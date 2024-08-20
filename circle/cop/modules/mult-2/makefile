ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

T=mul2
exe=../../crcl_$(PLAT)$(EEXT)

all: o $(exe) o/$T.tt

o:
	mkdir -p o

clean:
	rm -rf o


o/$T.tt: $T.cr
	$(exe) -ca $<
	mv $<.ttb $@
