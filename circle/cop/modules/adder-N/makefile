ifeq ($(OS),Windows_NT)
PLAT=w
else
PLAT=u
endif

#T=
exe=../../../crcl_$(PLAT)$(EEXT)

all: o $(exe) o/add3.tt

o:
	mkdir -p o

clean:
	rm -rf o


o/add3.tt: add3.cr
	$(exe) -ca $<
	mv $<.ttb $@
