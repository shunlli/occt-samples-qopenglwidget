#ifndef LINEEXTEND_H
#define LINEEXTEND_H

#include "gp_Pnt.hxx"
#include <math.h>

/*
            Cross calculation to find point C. Given point A,B & lenght AC.

            A-----------B------------C
            (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

            AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
            AC = 1000

            Xc = Xa + (AC * (Xb - Xa) / AB)
            Yc = Ya + (AC * (Yb - Ya) / AB)
*/

/*
    //! Usage:
    gp_Pnt A={0,0,0};
    gp_Pnt B={100,0,0};
    gp_Pnt C;

    LineExtend(A,B).ByExtension(50,C);
    std::cout<<"ByExtension Cx:"<<C.X()<<" Cy:"<<C.Y()<<" Cz:"<<C.Z()<<std::endl;

    LineExtend(A,B).ByTotal(175,C);
    std::cout<<"ByTotal Cx:"<<C.X()<<" Cy:"<<C.Y()<<" Cz:"<<C.Z()<<std::endl;
*/

//! Extend a line p1,p2
class LineExtend
{
public:

    gp_Pnt A,B;
    LineExtend(gp_Pnt _A, gp_Pnt _B) : A(_A), B(_B)  {}

    //! Preprocess.
    double AB = sqrt( pow(B.X()-A.X(),2) + pow(B.Y()-A.Y(),2) + pow(B.Z()-A.Z(),2));

    //! Get point by given total new line lenght AC.
    void ByTotal(double AC, gp_Pnt &C){
       CommonCode(AC,C);
    };

    //! Get new point by given the line extension value L.
    void ByExtension(double L, gp_Pnt &C){
        double AC=L+AB;
        CommonCode(AC,C);
    }
private:
    void CommonCode(double AC, gp_Pnt &C){
        C.SetX( A.X() + (AC * (B.X() - A.X()) / AB));
        C.SetY( A.Y() + (AC * (B.Y() - A.Y()) / AB));
        C.SetZ( A.Z() + (AC * (B.Z() - A.Z()) / AB));
    }
};

#endif // LINEEXTEND_H













