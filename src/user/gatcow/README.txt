this uses gatcou - use modmul4

*** TB FIXME

NOT USING MPIR

1. Update git checkout - git pull
2. in 'e3work/src' do
	make clean
	make bob USER=user/gatcou
3. in 'here' do
	make clean
	make


WITH MPIR

0. Update git checkout - git pull
1. in 'e3worl/3p' do
	make MPIR
2. in 'e3work/src' do
	make clean
	make bob USER=user/gatcou MPIR=1
3. in 'here' do
	make clean
	make MPIR=1

