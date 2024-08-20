// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#pragma once

#include "e3int.h"

namespace gc = e3::gatcou;


#define GSAV gc::Saver saver
#define GCi0 gc::cgates(i==0,saver)
#define GC_on gc::cgates(true,saver)
#define GC_off gc::cgates(false,saver)
#define GCi(x) gc::cgates(i==(x),saver)
#define GCx(x) gc::cgates((x),saver)
#define GCseq gc::crit(true,saver)

