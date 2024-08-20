
# input
(a1,0,0)=o/dec(x1,x2,x3)
(a2,0,0)=o/dec(z1,z2,z3)

# NAND
a = !(a1*a2)

# hashing
r2 = x1^z2^x3
r3 = z1^x2^z3

# output
(y1,y2,y3)=o/enc(a,r2,r3)
