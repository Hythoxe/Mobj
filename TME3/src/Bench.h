#ifndef  BENCH_H
#define  BENCH_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cstdlib>
#include "Timer.h"


namespace vector_bench{

    void backInsert    ();
    void frontInsert   ();
    void sortEachInsert();

}

namespace list_bench{

    void backInsert    ();
    void frontInsert   ();
    void sortEachInsert();

}

namespace map_bench{

    void insert();

}

#endif