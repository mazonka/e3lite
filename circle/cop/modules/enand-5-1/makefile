ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

T=a
exe=../../../crcl_$(PLAT)$(EEXT)

all: o $(exe) o/dec o/d2e.tt o/nand.tt o/tbed.tt o/nand.ta

o:
	mkdir -p o

clean:
	rm -rf o


o/dec: $T.bbs
	$(exe) -bc $<
	mv $T.bbs.2.cir o/enc
	mv $T.bbs.1.cir o/dec

o/hash: hash.bbs
	$(exe) -bgc@ $<
	mv hash.bbs.1.cir o/hash
	mv hash.bbs.2.cir o/hash2

o/d2e.tt: o/d2e.bdd
	$(exe) -ct $<
	mv o/d2e.bdd.ttb $@

o/d2e.bdd: $T.d2e.cir o/dec o/enc
	$(exe) -cb $<
	mv $T.d2e.cir.bdd $@

o/nand.tt: o/nand.bdd
	$(exe) -ct $<
	mv o/nand.bdd.ttb $@

o/nand.ta: o/nand.bdd
	$(exe) -ca $<
	mv o/nand.bdd.ttb $@

o/nand.bdd: $T.nand.cir o/dec o/enc o/hash
	$(exe) -cb $<
	mv $T.nand.cir.bdd $@

o/tbed.tt: o/tbed.bdd
	$(exe) -ct $<
	mv o/tbed.bdd.ttb $@

o/tbed.bdd: $T.tbed.cir o/dec o/enc
	$(exe) -cb $<
	mv $T.tbed.cir.bdd $@




