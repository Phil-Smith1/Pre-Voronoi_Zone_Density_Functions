#include "Spherical_Cap.h"
#include "General_Spherical_Wedge.h"
#include "Intersection_Of_Two_Lines3D.h"
#include "Circular_Intersection_Of_Sphere_And_Plane.h"
#include "Intersection_Of_Plane_And_Circle.h"
#include "Intersection_Pts_Of_Plane_And_Circle.h"
#include "Tetrahedron_Volume.h"

double General_Spherical_Cone ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l1, l2 );
    
    if (Norm( s.c, vertex) >= s.r - tiny_num)
    {
        double sp1 = Sphere_Plane_Distance( s, p1 ), sp2 = Sphere_Plane_Distance( s, p2 ), sp3 = Sphere_Plane_Distance( s, p3 );
        
        if (sp1 <= -s.r + tiny_num || sp2 <= -s.r + tiny_num || sp3 <= -s.r + tiny_num) return 0;
        
        else if (sp1 >= s.r - tiny_num && sp2 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return s.vol;
        
        else if (sp1 >= s.r - tiny_num && sp2 >= s.r - tiny_num) return Spherical_Cap( s, p3 );
        
        else if (sp1 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return Spherical_Cap( s, p2 );
        
        else if (sp2 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return Spherical_Cap( s, p1 );
        
        else if (sp1 >= s.r - tiny_num) return General_Spherical_Wedge( s, p2, p3 );
        
        else if (sp2 >= s.r - tiny_num) return General_Spherical_Wedge( s, p1, p3 );
        
        else if (sp3 >= s.r - tiny_num) return General_Spherical_Wedge( s, p1, p2 );
        
        else
        {
            Circle3D c1 = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
            Circle3D c2 = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
            Circle3D c3 = Circular_Intersection_Of_Sphere_And_Plane( s, p3 );
            
            if (!Intersection_Of_Plane_And_Circle( p2, c1 ))
            {
                if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                
                else if (p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            }
            
            if (!Intersection_Of_Plane_And_Circle( p3, c1 ))
            {
                if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                
                else if (p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
            }
            
            if (!Intersection_Of_Plane_And_Circle( p2, c3 ))
            {
                if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE && p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                
                else if (p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            }
            
            if (Intersection_Of_Plane_And_Circle( p2, c1 ) && Intersection_Of_Plane_And_Circle( p3, c1 ) && Intersection_Of_Plane_And_Circle( p2, c3 ))
            {
                P3 i1, i2, i3, i4, i5, i6;
                
                Intersection_Pts_Of_Plane_And_Circle( p2, c1, i1, i2 );
                Intersection_Pts_Of_Plane_And_Circle( p3, c1, i3, i4 );
                Intersection_Pts_Of_Plane_And_Circle( p2, c3, i5, i6 );
                
                if (Norm( i1, i2 ) < 1e-6)
                {
                    if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                    
                    else if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else if (p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
                }
                
                if (Norm( i3, i4 ) < 1e-6)
                {
                    if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return 0;
                    
                    else if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else if (p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                }
                
                if (Norm( i5, i6 ) < 1e-6)
                {
                    if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE && p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                    
                    else if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                    
                    else if (p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
                }
                
                bool positive_side1, positive_side2, positive_side3;
                
                if (p1.oriented_side( i5 ) == ON_NEGATIVE_SIDE || p1.oriented_side( i6 ) == ON_NEGATIVE_SIDE) positive_side1 = false;
                else positive_side1 = true;
                
                if (p2.oriented_side( i3 ) == ON_NEGATIVE_SIDE || p2.oriented_side( i4 ) == ON_NEGATIVE_SIDE) positive_side2 = false;
                else positive_side2 = true;
                
                if (p3.oriented_side( i1 ) == ON_NEGATIVE_SIDE || p3.oriented_side( i2 ) == ON_NEGATIVE_SIDE) positive_side3 = false;
                else positive_side3 = true;
                
                int num_pos = 0;
                
                if (positive_side1) ++num_pos;
                if (positive_side2) ++num_pos;
                if (positive_side3) ++num_pos;
                
                if (num_pos == 0) return 0;
                
                else if (num_pos == 1)
                {
                    if (positive_side1) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else if (positive_side2) return General_Spherical_Wedge( s, p1, p3 );
                    
                    else if (positive_side3) return General_Spherical_Wedge( s, p1, p2 );
                }
                
                else
                {
                    double volume = s.vol - Spherical_Cap( s, p1.opposite() ) - Spherical_Cap( s, p2.opposite() ) - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p2.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
                    
                    return volume;
                }
            }
        }
    }
    
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
    
    P3 pt1, pt2, pt3, i1, i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p2, c, i1, i2 );
    
    if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt3 = i1;
    else pt3 = i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (p2.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt2 = i1;
    else pt2 = i2;
    
    c = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (p1.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt1 = i1;
    else pt1 = i2;
    
    double tet_volume = Tetrahedron_Volume( vertex, pt1, pt2, pt3 );
    
    Pl3 p4( pt1, pt2, pt3 );
    
    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE) p4 = p4.opposite();
    
    double cap_volume = Spherical_Cap( s, p4 );
    
    Pl3 p5 = p1.opposite();
    Pl3 p6 = p2.opposite();
    Pl3 p7 = p3.opposite();
    
    double wedge_volume1 = General_Spherical_Wedge( s, p5, p4 );
    double wedge_volume2 = General_Spherical_Wedge( s, p6, p4 );
    double wedge_volume3 = General_Spherical_Wedge( s, p7, p4 );
    
    return tet_volume + cap_volume - wedge_volume1 - wedge_volume2 - wedge_volume3;
}