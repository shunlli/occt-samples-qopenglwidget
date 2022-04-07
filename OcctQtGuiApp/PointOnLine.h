#ifndef POINTONLINE_H
#define POINTONLINE_H

#include <gp_Pnt.hxx>

class PointOnLine
{
public:
    PointOnLine(gp_Pnt _p1_line, gp_Pnt _p2_line, gp_Pnt _p3_thePoint): p1(_p1_line), p2(_p2_line), p3(_p3_thePoint) {};

    bool isOnLine(){
        double l0=sqrt(pow(p2.X()-p1.X(),2)+pow(p2.Y()-p1.Y(),2)+pow(p2.Z()-p1.Z(),2));
        double l1=sqrt(pow(p1.X()-p3.X(),2)+pow(p1.Y()-p3.Y(),2)+pow(p1.Z()-p3.Z(),2));
        double l2=sqrt(pow(p2.X()-p3.X(),2)+pow(p2.Y()-p3.Y(),2)+pow(p2.Z()-p3.Z(),2));

        //! Result.
        if(l0>(l1+l2)-EPS && l0<(l1+l2)+EPS){
            if(debug){std::cout<<"point is on line";}
            return 1;
        };
        if(debug){std::cout<<"point is not on the line";}
        return 0;
    };

private:
    double EPS=0.001;
    gp_Pnt p1, p2, p3;
    bool debug=0;
};

#endif // POINTONLINE_H
