// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#pragma once

#include "e3int.h"

namespace gw = e3::gatcow;

// FIXME
// use indirect contact like in this example
#define PUSHMOD_NAME1(x) push_mod_ ## x
#define PUSHMOD_NAME2(x) PUSHMOD_NAME1(x)
#define PUSHMOD(x) PushMod PUSHMOD_NAME2(__LINE__) (x)
// end of example


#ifdef GC_USE_MACROS
#define HERE (std::string(__func__)+":"+std::to_string(__LINE__))
#define GC_share gw::Share gc_dummy_##__LINE__(HERE,true)
#define GC_path(i) gw::Share gc_dummy_##__LINE__(HERE+":"+std::to_string(i),true)
#define GC_PAR gw::PathBlock gc_dummy_##__LINE__(gw::PAR)
#define GC_SEQ gw::PathBlock gc_dummy_##__LINE__(gw::SEQ)
#define GC_block(c) gw::PathBlock gc_dummy_##__LINE__(#c)
#define GC_valid gw::PathBlock::isvalid()
#endif


