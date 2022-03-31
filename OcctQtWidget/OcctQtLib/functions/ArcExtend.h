#ifndef ARCEXTEND_H
#define ARCEXTEND_H

#include "gp_Pnt.hxx"
#include "gp_Circ.hxx"
#include <math.h>
#include <GC_MakeArcOfCircle.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <AIS_Shape.hxx>

//! Make conversion's easy:
#define toRadians M_PI/180.0
#define toDegrees (180.0/M_PI)

/* Usage :
                #include "ArcExtend.h"

                gp_Pnt A={0,0,0};
                gp_Pnt B={100,0,0};
                gp_Pnt CP={50,0,0};
                ArcExtend(A,B,CP).ByAngle(-5,5);

                //! or
                Handle(AIS_Shape) myArc=ArcExtend(A,B,CP).ByAngle(-5,5);

                //! or
                gp_Pnt NewA, NewB;
                ArcExtend(A,B,CP).GetNewPoints(-5,5,NewA,NewB);

                std::cout<<"NewA.x:"<<NewA.X()<<" y:"<<NewA.Y()<<" z:"<<NewA.Z()<<std::endl;
                std::cout<<"NewB.x:"<<NewB.X()<<" y:"<<NewB.Y()<<" z:"<<NewB.Z()<<std::endl;
*/

//! Extend a arc.
class ArcExtend
{
public:
    bool debug=1;
    Handle(Geom_TrimmedCurve) aArcOfCircle;
    gp_Pnt A,B,CP;
    //! Circle endpoints A,B circle centerpoint CP.
    ArcExtend(gp_Pnt _A, gp_Pnt _B, gp_Pnt _CP) : A(_A), B(_B), CP(_CP){}

    //! Preprocess Radius R.
    double R = CP.Distance(A);

    //! Get new point by given a offset angle in degrees. (incremented angle + or - is valid).
    Handle(AIS_Shape) ByAngle(double AddStartDegrees, double AddEndDegrees){

        SharedCode(AddStartDegrees, AddEndDegrees);
        TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aArcOfCircle);
        return new AIS_Shape(aEdge2);
    }

    void GetNewPoints(double AddStartDegrees, double AddEndDegrees, gp_Pnt &NewA, gp_Pnt &NewB){

        SharedCode(AddStartDegrees, AddEndDegrees);
        NewA=aArcOfCircle->StartPoint();
        NewB=aArcOfCircle->EndPoint();
    }

private:
    void SharedCode(double AddStartDegrees, double AddEndDegrees){
        gp_Dir dir(0,0,1);
        gp_Circ circle(gp_Ax2(CP,dir),R);

        aArcOfCircle = GC_MakeArcOfCircle(circle,A,B,0);

        double u1=aArcOfCircle->FirstParameter();
        double u2=aArcOfCircle->LastParameter();

        if(debug){
            std::cout<<"original arc values:"<<std::endl;
            std::cout<<"startparameter u1:"<<u1*toDegrees<<" endparameter u2:"<<u2*toDegrees<<std::endl;
        }

        u1+=AddStartDegrees*toRadians;
        u2+=AddEndDegrees*toRadians;
        aArcOfCircle->SetTrim(u1,u2,Standard_True,Standard_True);

        if(debug){
            std::cout<<"modified arc values:"<<std::endl;
            std::cout<<"startparameter u1:"<<u1*toDegrees<<" endparameter u2:"<<u2*toDegrees<<std::endl;
        }
    }
};

#endif // ARCEXTEND_H
