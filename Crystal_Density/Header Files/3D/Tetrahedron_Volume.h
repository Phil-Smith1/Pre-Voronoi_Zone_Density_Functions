#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

double Tetrahedron_Volume ( P3 const& p1, P3 const& p2, P3 const& p3, P3 const& p4 );