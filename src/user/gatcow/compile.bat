set R=../../
set O=%R%bt_win
set OB=%O%/secint.obj %O%/cgtshared.obj

@rm -f bob.exe
cl -EHsc -Ox -I%R% main.cpp %OB% -Febob.exe
@rm main.obj
