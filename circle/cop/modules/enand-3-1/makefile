ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

#T=
exe=../../../crcl/crcl.exe

all: o $(exe) o/dec o/d2e.tt o/enand.tt o/tbed.tt

o:
	mkdir -p o

clean:
	rm -rf o


o/dec: bbs
	$(exe) -bgc@ $<
	mv bbs.2.cir o/enc
	mv bbs.1.cir o/dec

o/d2e.tt: o/d2e.bdd
	$(exe) -ct $<
	mv o/d2e.bdd.ttb $@

o/d2e.bdd: d2e.cr o/dec o/enc
	$(exe) -cb $<
	mv d2e.cr.bdd $@

o/enand.tt: o/enand.bdd
	$(exe) -ct $<
	mv o/enand.bdd.ttb $@

o/enand.bdd: enand.cr o/dec o/enc
	$(exe) -cb $<
	mv enand.cr.bdd $@

o/tbed.tt: o/tbed.bdd
	$(exe) -ct $<
	mv o/tbed.bdd.ttb $@

o/tbed.bdd: tbed.cr o/dec o/enc
	$(exe) -cb $<
	mv tbed.cr.bdd $@




