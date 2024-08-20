// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <vector>
#include <iomanip>

#define GC_USE_MACROS

#include "e3int.h"

using namespace std;

void xf()
{
    TypeBool b;
    GC_SEQ;
    e3::gatcow::Share gc_dummy(__func__);
    b.g_and(b);
}

void x2()
{
    GC_SEQ;
    e3::gatcow::Share gc_(__func__);
    xf();
}

void x1()
{
    GC_SEQ;
    e3::gatcow::Share gc_(__func__);
    xf();
}


int x_main(int ac, const char * av[])
try
{
    GC_block pb;

    x1();
    x2();
    x1();
    x2();

    cout << pb.sum();
	return 0;
}


catch (int e)
{
    cout << "error (int): " << e << "\n";
    return 1;
}
catch (string e)
{
    cout << "error (str): " << e << "\n";
    return 1;
}
catch (const char * e)
{
    cout << "error (cc): " << e << "\n";
    return 1;
}
catch (...)
{
    cout << "Unknown exception\n";
    return 1;
}




