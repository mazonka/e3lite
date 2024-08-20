@call cr -cn cir
@call cr -cl cir.out

@call cr -cb cir
@call cr -cl cir.bdd

@cl -nologo main_bdd.c
@cl -nologo main_out.c

main_bdd.exe
main_out.exe
