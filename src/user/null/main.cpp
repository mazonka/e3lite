// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "e3int.h"
#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

using namespace std;


int main(int ac, char * av[])
try
{
	e3::Bigun a(5);
	auto b = a;
	b[1] = b(2);
    std::cout << "expect (57) : " << a << b << '\n' ;
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
