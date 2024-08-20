# Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
import os

circuits = []
circuits.append( { 'encryption' : 'bddn', 'circuit' : 'bddn', 'compile' : 'CUDD=1' } )
# circuits.append( { 'encryption' : 'tfhe', 'circuit' : 'tfhe', 'compile' : 'TFHE=1' } )
# circuits.append( { 'encryption' : 'pil' , 'circuit' : 'pil' , 'compile' : 'MPIR=1' } )
benchs = [ 'bsort', 'fact', 'fib', 'isort', 'jen', 'matrix', 'sieve', 'speck' ]
benchs = [ 'fib' ]
size = '32' # 8 | 32
lambdas = ['4'] + [str(l) for l in range(10,101,10)]
# lambdas = ['512']
seeds = [str(s) for s in range(10)]
# seeds = ['']

src = '../../..'
user = 'user/bench/std'
cgt = 'cgt_auto.cfg'
timeCSV = 'time_terminator.csv'

def main():
    # write CSV header
    if not os.path.isfile(timeCSV):
        items = ['encryption']
        for bench in benchs:
            items.append('{}-{}'.format(bench, size))
        writeRowCSV(filename=timeCSV, items=items)

    # BDDs first
    for circuit in circuits:
        if all( x not in circuit['encryption'] for x in ['bdd', 'pil'] ):
            continue
        for l in lambdas:
            for seed in seeds:
                writeCGT(cgt, circuit['encryption'], circuit['circuit'], size, l, seed)
                row = [ '{}-{}'.format(circuit['encryption'], l) ]
                for bench in benchs:
                    clean(src)
                    compile(src, user, bench, cgt, circuit['compile'])
                    run(src, user)
                    row.append(getTime())
                writeRowCSV(filename=timeCSV, items=row)

    exit(0)
    # Non-BDD after
    for circuit in circuits:
        if 'bdd' in circuit['encryption']:
            continue
        writeCGT(cgt, circuit['encryption'], circuit['circuit'], size)
        row = [ circuit['encryption'] ]
        for bench in benchs:
            clean(src)
            compile(src, user, bench, cgt, circuit['compile'])
            run(src, user)
            row.append(getTime())
        writeRowCSV(filename=timeCSV, items=row)

def clean(src):
    command = 'cd {} && rm -rf *.key secint.* x.* && make c'.format(src)
    # command = 'cd {} && rm -rf *.key secint.* x.*'.format(src)
    os.system(command)

def compile(src, user, bench, cgt, param):
    # command = 'cd {0} && make c && rm -rf *key* x.* && make USER={1}/{2} CGT={1}/{3} {4}'.format(src, user, bench, cgt, param)
    command = 'cd {0} && make USER={1}/{2} CGT={1}/{3} {4}'.format(src, user, bench, cgt, param)
    os.system(command)

def getTime():
    with open('out.txt') as fin:
        items = fin.read().split(' ')
        t = items[1] if len(items) > 2 else '?'
    return t

def run(src, user):
    command = 'cd {} && ./bob.exe > {}/out.txt'.format(src, user)
    os.system(command)

def writeCGT(filename, encryption, circuit, size, l=None, seed=''):
    with open(filename, 'w') as fout:
        fout.write('# Generated by terminator.py\n\n')
        fout.write('password = hello_world{}\n\n'.format(seed))
        fout.write('@circuitDB = {}\n'.format(circuit))
        fout.write('@sizes = {}\n'.format(size))
        if l is not None:
            fout.write('@lambda = {}\n'.format(l))
            if 'bdd' in encryption:
                fout.write('@kernel = bbs\n')
                fout.write('@formula = FLF\n')
                fout.write('@compile = [ unx: g++ $.cpp -o $.exe ][ win: cl -EHsc -Ox -nologo $.cpp ]\n')
        fout.write('\nType : circuit\n')
        fout.write('{\n')
        fout.write('\tpostfix = Ep\n')
        fout.write('\tpostneg = En\n')
        fout.write('\tencryption = {}\n'.format(encryption))
        fout.write('}\n')

def writeRowCSV(filename, items):
    with open(filename, 'a') as fout:
        strout = ''
        for item in items:
            strout += item+','
        fout.write('{}\n'.format(strout[:-1]))

if __name__ == '__main__':
    main()
