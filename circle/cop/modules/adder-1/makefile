ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

#T=
exe=../../crcl_$(PLAT)$(EEXT)

all: o $(exe) o/add1.tt

o:
	mkdir -p o

clean:
	rm -rf o


o/add1.tt: add1.cr
	$(exe) -ct $<
	mv $<.ttb $@
