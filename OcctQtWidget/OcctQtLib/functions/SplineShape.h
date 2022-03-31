#ifndef SPLINESHAPE_H
#define SPLINESHAPE_H

//! Opencascade.
#include <gp_Pnt.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

//! Libspline.
#include <libspline/cubic_spline.h>

class SplineShape
{
public:

    std::vector<gp_Pnt> pointvec;

    //! Initialize.
    SplineShape( std::vector<gp_Pnt> _pointvec) : pointvec(_pointvec) {

    }

    //! Return the shape.
    Handle(AIS_Shape) Shape(){

         std::vector<Vector3d> path; // libspline input
         for(unsigned int i=0; i<pointvec.size(); i++){
             path.push_back(Vector3d(pointvec.at(i).X(),pointvec.at(i).Y(),pointvec.at(i).Z()));
         }
         CubicSpline c_spline(path,20);
         c_spline.BuildSpline(path);
         std::vector<double> c_pathx(c_spline.GetPositionProfile().size());
         std::vector<double> c_pathy(c_spline.GetPositionProfile().size());
         std::vector<double> c_pathz(c_spline.GetPositionProfile().size());

         // Store wire points(p) into pointvector (pvec)
         gp_Pnt p;
         std::vector<gp_Pnt> pvec;
         // Get profile data for position, speed, acceleration, and curvature
         std::vector<double> ti(c_spline.GetPositionProfile().size());
         for(unsigned int i=0;i<c_pathx.size();++i)
         {
             c_pathx[i] = c_spline.GetPositionProfile()[i].x();
             c_pathy[i] = c_spline.GetPositionProfile()[i].y();
             c_pathz[i] = c_spline.GetPositionProfile()[i].z();

             p= {c_pathx[i],c_pathy[i],c_pathz[i]};
             pvec.push_back(p);
         }

         //! Create a linewire.
         BRepBuilderAPI_MakeWire aWire;
         TopoDS_Edge edge;
         gp_Pnt p1=pvec[0], p2={0,0,0};
         for(unsigned int i=1; i<pvec.size(); i++){

             //! A system to avoid duplicates.
             p2=pvec.at(i);
             if(p1.X()!=p2.X() || p1.Y()!=p2.Y() || p1.Z()!=p2.Z()){
                 edge = BRepBuilderAPI_MakeEdge(p1,p2);
                 aWire.Add(edge);
                 p1=p2;
             } else {
                 std::cout<<"duplicate from spline function"<<std::endl;
             }
         }

        Handle(AIS_Shape) myShape= new AIS_Shape(aWire);
        return myShape;
    }
};

#endif // SPLINESHAPE_H
