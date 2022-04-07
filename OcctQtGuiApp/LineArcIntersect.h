#ifndef LINEARCINTERSECT_H
#define LINEARCINTERSECT_H

#include <gp_Pnt.hxx>
#include <vector>
#include <PointOnLine.h>

class LineArcIntersect
{
public:
    //! Line startpoint : p0.
    //! Line endpoint   : p1.
    //! Arc startpoint  : arc_p0.
    //! Arc endpoint    : arc_p1.
    //! Arc centerpoint : Arc_cp.
    //! Arc radius      : radius.
    LineArcIntersect(gp_Pnt _line_p0, gp_Pnt _line_p1, gp_Pnt _arc_cp, double _radius) : p0(_line_p0), p1(_line_p1), cp(_arc_cp), radius(_radius) {}

    //! Return intersections.
    bool getIntersections(std::vector<gp_Pnt> &pvec)
    {
        double cx = cp.X();
        double cy = cp.Y();
        double cz = cp.Z();

        double px = p0.X();
        double py = p0.Y();
        double pz = p0.Z();

        double vx = p1.X() - px;
        double vy = p1.Y() - py;
        double vz = p1.Z() - pz;

        double A = vx * vx + vy * vy + vz * vz;
        double B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
        double C = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
                pz * pz - 2 * pz * cz + cz * cz - radius * radius;

        //! discriminant
        double D = B * B - 4 * A * C;

        double t1 = (-B - Sqrt(D)) / (2.0 * A);

        gp_Pnt solution1;
        solution1.SetX(p0.X() * (1 - t1) + t1 * p1.X());
        solution1.SetY(p0.Y() * (1 - t1) + t1 * p1.Y());
        solution1.SetZ(p0.Z() * (1 - t1) + t1 * p1.Z());

        double t2 = (-B + Sqrt(D)) / (2.0 * A);
        gp_Pnt solution2;
        solution2.SetX(p0.X() * (1 - t2) + t2 * p1.X());
        solution2.SetY(p0.Y() * (1 - t2) + t2 * p1.Y());
        solution2.SetZ(p0.Z() * (1 - t2) + t2 * p1.Z());


        if (D < 0 || t1 > 1 || t2 >1)
        {
            if(debug){
                std::cout<<"nothing..?"<<std::endl;
            }
            return false;
        }
        else if (D == 0)
        {
            if(PointOnLine(p0,p1,solution1).isOnLine()){
                pvec.push_back(solution1);
                if(debug){
                    std::cout<<"one solution"<<std::endl;
                }
                return true;
            }
        }
        else
        {
            if(PointOnLine(p0,p1,solution1).isOnLine()){
                pvec.push_back(solution1);
            }
            if(PointOnLine(p0,p1,solution2).isOnLine()){
                pvec.push_back(solution2);
            }
            if(debug){
                std::cout<<"two solutions"<<std::endl;
            }
            return true;
        }
        return false;
    };
private:
    gp_Pnt p0, p1, cp;
    double radius;
    bool debug=0;
};

#endif // LINEARCINTERSECT_H

















