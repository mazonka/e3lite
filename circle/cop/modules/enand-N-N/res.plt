set logscale y
plot [0:200] [0.4:] "res.dat" w l lw 2 t "size"
replot "res.dat" u 1:3 w l  lw 2 t "time"
replot "res.dat" u 1:4 w l  lw 2 t "size MX"
replot "res.dat" u 1:5 w l  lw 2 t "time MX"

replot "res.dat" u 1:2 w p  lw 2 t "size"
replot "res.dat" u 1:3 w p  lw 2 t "time"
replot "res.dat" u 1:4 w p  lw 2 t "size MX"
replot "res.dat" u 1:5 w p  lw 2 t "time MX"

pause 10000
