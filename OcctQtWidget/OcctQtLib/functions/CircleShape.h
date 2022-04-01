#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

//! Opencascade.
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <AIS_Shape.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <TopoDS_Edge.hxx>

class CirlceShape
{
public:

    gp_Pnt cp, p;
    double radius=0.0;
    //! Circle given centerpoint cp and one point on the circle circumfence. Then request a plane to draw in:
    //!  1. Top
    //!  2. Right
    //!  3. Bottom.
    CirlceShape(gp_Pnt _cp, gp_Pnt _p) : cp(_cp), p(_p)  {
        radius=cp.Distance(p);
    }

    //! Return the shape in Top plane => gp_Ax2 plane=gp::XOY()
    Handle(AIS_Shape) ShapeTopPlane(){
        gp_Dir dir(0,0,1);
        gp_Circ circle(gp_Ax2(cp, dir),radius);
        TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(circle);
        Handle(AIS_Shape) myShape=new AIS_Shape(aEdge);
        return myShape;
    }

    //! Return the shape in Right plane => gp_Ax2 plane=gp::YOZ();
    Handle(AIS_Shape) ShapeRightPlane(){
        gp_Dir dir(1,0,0);
        gp_Circ circle(gp_Ax2(cp, dir),radius);
        TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(circle);
        Handle(AIS_Shape) myShape=new AIS_Shape(aEdge);
        return myShape;
    }

    //! Return the shape in Front plane => gp_Ax2 plane=gp::ZOX();
    Handle(AIS_Shape) ShapeFrontPlane(){
        gp_Dir dir(0,1,0);
        gp_Circ circle(gp_Ax2(cp, dir),radius);
        TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(circle);
        Handle(AIS_Shape) myShape=new AIS_Shape(aEdge);
        return myShape;
    }
};

#endif // CIRCLESHAPE_H
