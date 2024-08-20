ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

exe=../../crcl_$(PLAT)$(EEXT)
exe=cr.bat

#all: o $(exe) o/dec o/d2e.bdd o/nand.bdd
all: o o/dec o/d2e.bdd o/nand.bdd

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

o/d2e.bdd: d2e o/dec o/enc
	$(exe) -cb $<
	mv d2e.bdd $@

o/nand.tt: o/nand.bdd
	$(exe) -ct $<
	mv o/nand.bdd.ttb $@

o/nand.ta: o/nand.bdd
	$(exe) -ca $<
	mv o/nand.bdd.ttb $@

o/nand.bdd: enand o/dec o/enc
	$(exe) -cb $<
	mv enand.bdd $@

o/tbed.tt: o/tbed.bdd
	$(exe) -ct $<
	mv o/tbed.bdd.ttb $@

o/tbed.bdd: tbed o/dec o/enc
	$(exe) -cb $<
	mv tbed.bdd $@




