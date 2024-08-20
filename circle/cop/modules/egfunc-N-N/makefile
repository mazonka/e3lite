ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

T=egfun
exe=../../crcl_$(PLAT)$(EEXT)

all: o $(exe) o/dec o/d2e.bdd o/$T.bdd

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

o/$T.tt: o/$T.bdd
	$(exe) -ct $<
	mv o/$T.bdd.ttb $@

o/$T.ta: o/$T.bdd
	$(exe) -ca $<
	mv o/$T.bdd.ttb $@

o/$T.bdd: $T o/dec o/enc
	$(exe) -cb $<
	mv $T.bdd $@

o/tbed.tt: o/tbed.bdd
	$(exe) -ct $<
	mv o/tbed.bdd.ttb $@

o/tbed.ta: o/tbed.bdd
	$(exe) -ca $<
	mv o/tbed.bdd.ttb $@

o/tbed.bdd: tbed o/dec o/enc
	$(exe) -cb $<
	mv tbed.bdd $@


