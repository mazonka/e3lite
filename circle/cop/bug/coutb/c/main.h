#define X 2
#define Y 2

#define FUNN1(x,xx,yy) x##xx##_##yy
#define FUNN2(x,xx,yy) FUNN1(x,xx,yy)

#define FUNNbdd FUNN2(cir_bdd_,X,Y)
#define FUNNout FUNN2(cir_out_,X,Y)


