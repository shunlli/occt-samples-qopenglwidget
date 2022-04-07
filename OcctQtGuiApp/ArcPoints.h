#ifndef ARCPOINTS_H
#define ARCPOINTS_H

#include <gp_Pnt.hxx>
#include <gp_Ax2.hxx>
#include <vector>
#include <ArcCenter.h>

//! This class has reverse engeneered code at some points with the help off the <ElCLib.hxx> class.
//! The function creates 3d arc points along the 3d arc curve.
//! This can be helpfull to calculate arc intersections with other primitives in other class.
class ArcPoints
{
public:
    ArcPoints(gp_Pnt arc_p0, gp_Pnt arc_p1, gp_Pnt arc_p2) : p0(arc_p0), p1(arc_p1), p2(arc_p2) {}


    //! The division is the resolution, a division of 50, gives back 51 points.
    std::vector<gp_Pnt> getPoints(unsigned int division){

        //! Point storage container.
        std::vector<gp_Pnt> pvec;

        //! Get 3d arc points along the curve, given a 3p_arc.
        gp_Pnt p1{0,0,0};
        gp_Pnt p2(50,50,0);
        gp_Pnt p3{100,0,0};
        gp_Pnt center=ArcCenter(p1,p2,p3).Arc_cp();
        double radius=ArcCenter(p1,p2,p3).Arc_radius();

        //! Get 3d arc orientation.
        double x1,y1,z1,x2,y2,z2,x3,y3,z3;
        p1.Coord(x1,y1,z1);
        p2.Coord(x2,y2,z2);
        p3.Coord(x3,y3,z3);
        gp_Dir Dir1(x2-x1,y2-y1,z2-z1);
        gp_Dir Dir2(x3-x2,y3-y2,z3-z2);
        gp_Dir Dir3 = Dir1.Crossed(Dir2);
        gp_Ax2 ArcPos(center,Dir3,Dir1);

        //! Max circle value is endpoint.
        //gp_Circ C(ArcPos,radius);
        double U_start = getCircleParameter(ArcPos,p1);   std::cout<<"U_start:"<<U_start<<std::endl;
        double U_end = getCircleParameter(ArcPos,p3);     std::cout<<"U_endt:"<<U_end<<std::endl;

        //! When cirlce end < start add a full circle.
        if(U_end<U_start){
            U_end+=2*M_PI;
        }

        double increment= (U_end-U_start)/division;

        for(double i=U_start; i<=U_end; i+=increment){

            gp_XYZ XDir = ArcPos.XDirection().XYZ();
            gp_XYZ YDir = ArcPos.YDirection().XYZ();
            gp_XYZ PLoc = ArcPos.Location  ().XYZ();
            Standard_Real A1 = radius * cos(i);
            Standard_Real A2 = radius * sin(i);

            gp_Pnt result;
            result.SetX(A1 * XDir.X() + A2 * YDir.X() + PLoc.X());
            result.SetY(A1 * XDir.Y() + A2 * YDir.Y() + PLoc.Y());
            result.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + PLoc.Z());

            std::cout<<"p.x:"<<result.X()<<" p.y:"<<result.Y()<<" p.z:"<<result.Z()<<std::endl;
        }

        return pvec;
    }

private:

    //! Borrowed from <ElCLib.hxx>
    double getCircleParameter(gp_Ax2 Pos, gp_Pnt P)
    {
        gp_Vec aVec(Pos.Location(), P);
        if (aVec.SquareMagnitude() < gp::Resolution())
            // coinciding points -> infinite number of parameters
            return 0.0;

        gp_Dir dir = Pos.Direction();
        // Project vector on circle's plane
        gp_XYZ aVProj = dir.XYZ().CrossCrossed(aVec.XYZ(), dir.XYZ());

        if (aVProj.SquareModulus() < gp::Resolution())
            return 0.0;

        // Angle between X direction and projected vector
        Standard_Real Teta = (Pos.XDirection()).AngleWithRef(aVProj, dir);

        if      (Teta < -1.e-16)  Teta += M_PI+M_PI;
        else if (Teta < 0)        Teta = 0;
        return Teta;
    }

    gp_Pnt p0,p1,p2;
};

#endif // ARCPOINTS_H
