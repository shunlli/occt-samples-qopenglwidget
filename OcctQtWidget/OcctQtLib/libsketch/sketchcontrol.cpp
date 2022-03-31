#include "sketchcontrol.h"
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <AIS_Shape.hxx>
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeArcOfCircle.hxx"
#include "GC_MakeCircle.hxx"
#include "Geom_Circle.hxx"
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <gp_Circ.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>

#include <Geom2dAdaptor_Curve.hxx>
#include <TColgp_Array1OfPnt.hxx>

#include <libspline/cubic_spline.h>
#include <libspline/bezier_spline.h>
using namespace Eigen;

SketchControl::SketchControl(Handle(AIS_InteractiveContext)& theContext, Handle(V3d_Viewer)& theViewer)
{
    myContext=theContext;
    myViewer=theViewer;
    TopoDS_Edge aEdge;

    //! Create some points to use, prevent duplicates.
    p0=new Geom_CartesianPoint(0,0,0);
    p1=new Geom_CartesianPoint(1,1,0); //! Y is set to enable a arc shape.
    p2=new Geom_CartesianPoint(2,0,0);
    p3=new Geom_CartesianPoint(3,0,0);
    p4=new Geom_CartesianPoint(3.5,0,0);
    mp=new Geom_CartesianPoint(4,0,0);


    //! Construct a line.
    myRubberLine = new AIS_Line(p0,p1);
    myRubberLine->SetColor(Quantity_NOC_RED);

    //! Construct a arc.
    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p0->Pnt(),p1->Pnt(),p2->Pnt());
    aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    myRubberArc= new AIS_Shape(aEdge);

    //! Construct a square.
    BRepBuilderAPI_MakeWire aWire;
    aEdge = BRepBuilderAPI_MakeEdge(p0->Pnt(),p1->Pnt());
    aWire.Add(aEdge);
    aEdge = BRepBuilderAPI_MakeEdge(p1->Pnt(),p2->Pnt());
    aWire.Add(aEdge);
    aEdge = BRepBuilderAPI_MakeEdge(p2->Pnt(),p3->Pnt());
    aWire.Add(aEdge);
    aEdge = BRepBuilderAPI_MakeEdge(p3->Pnt(),p0->Pnt());
    aWire.Add(aEdge);
    myRubberSquare = new AIS_Shape(aWire);

    //! Construct a circle.
    myRubberPoint = new AIS_Shape(aEdge);

    //! Construct a circle.
    myRubberCircle = new AIS_Shape(aEdge);

    //! Construct a spline.
    myRubberSpline = new AIS_Shape(aEdge);

    //! Construct a bezier.
    myRubberBezier = new AIS_Shape(aEdge);

    //! Construct a slot.
    myRubberSlotArcA = new AIS_Shape(aEdge);
    myRubberSlotArcB = new AIS_Shape(aEdge);
    myRubberSlotEdgeA = new AIS_Shape(aEdge);
    myRubberSlotEdgeB = new AIS_Shape(aEdge);
    myRubberSlotPointA = new AIS_Shape(aEdge);
    myRubberSlotPointB = new AIS_Shape(aEdge);

    //! Test the by "&" reference context:
    //!
    //! 1.
    //!     TopoDS_Edge edge = BRepBuilderAPI_MakeEdge({0,0,0},{100,0,0});
    //!     Handle(AIS_Shape) aShape= new AIS_Shape(edge);
    //!     myContext->Display(aShape,Standard_False);
    //! 2.
    //!     Handle(Geom_CartesianPoint)	p0=new Geom_CartesianPoint(0,0,0);
    //!     Handle(Geom_CartesianPoint)	p1=new Geom_CartesianPoint(100,0,0);
    //!     Handle(AIS_Line) aLine = new AIS_Line(p0,p1);
    //!     myContext->Display(aLine,Standard_False);
}

void SketchControl::SetColor(const Quantity_NameOfColor theColor){
    myColor=theColor;
}

void SketchControl::Cancel(){
    myMouseClick=0;
    myContext->Remove(myRubberLine,Standard_True);
    myContext->Remove(myRubberArc,Standard_True);
    myContext->Remove(myRubberSquare,Standard_True);

    if(myPvec.size()>2){
        myPvec.pop_back();
        spline_preview(myPvec,1);
    }
    myPvec.clear();

    remove_all_temp_points();
}

void SketchControl::SetPrimitiveType(enum PrimitiveType thePrimimitveType){
    myPrimitiveType=thePrimimitveType;
    myMouseClick=0;
}

void SketchControl::on_lineEdit_returnPressed(gp_Pnt p){
    mp->SetCoord(p0->X()+p.X(),p0->Y()+p.Y(),p0->Z()+p.Z());
    OnMouseMoveEvent(1);
}

void SketchControl::add_temp_point_to_preview(gp_Pnt p){
    TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p);
    myRubberPointVec.push_back(new AIS_Shape(vertex));
    myContext->Display(myRubberPointVec.back(),AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
}

void SketchControl::remove_all_temp_points(){

    for(unsigned int i=0; i<myRubberPointVec.size(); i++){
        myContext->Remove(myRubberPointVec.at(i),Standard_False);
        myRubberPointVec.at(i).Nullify();
    }
    myRubberPointVec.clear();
    myViewer->Redraw();
}

//! A,b is the line. C is the point to determine. (xoy plane)
int SketchControl::side_of_line_xoy(gp_Pnt a, gp_Pnt b, gp_Pnt c){
    //! Return 0 on the line, and +1 on one side, -1 on the other side.
    return ((b.X() - a.X()) * (c.Y() - a.Y()) - b.Y() - a.Y()) * (c.X() - a.X());
}

//! A,b is the line. C is the point to determine. (yoz plane)
int SketchControl::side_of_line_yoz(gp_Pnt a, gp_Pnt b, gp_Pnt c){
    //! Return 0 on the line, and +1 on one side, -1 on the other side.
    return ((b.Z() - a.Z()) * (c.Y() - a.Y()) - b.Y() - a.Y()) * (c.Z() - a.Z());
}

//! A,b is the line. C is the point to determine. (zox plane)
int SketchControl::side_of_line_zox(gp_Pnt a, gp_Pnt b, gp_Pnt c){
    //! Return 0 on the line, and +1 on one side, -1 on the other side.
    return ((b.Z() - a.Z()) * (c.X() - a.X()) - b.X() - a.X()) * (c.Z() - a.Z());
}

void SketchControl::spline_preview(std::vector<gp_Pnt> pointvec, bool set_final_shape){

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

    myRubberSpline->SetShape(aWire);
    myContext->Display(myRubberSpline,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
    myContext->Redisplay(myRubberSpline,Standard_True);

    if(set_final_shape){
        myContext->Remove(myRubberSpline,Standard_False);

        //! Building the Resulting Compound
        TopoDS_Compound aRes;
        BRep_Builder aBuilder;
        aBuilder.MakeCompound (aRes);
        aBuilder.Add (aRes, myRubberSpline->Shape());

        //! Draw the user controlpoints.
        TopoDS_Vertex vertex;
        for(unsigned int i=0; i<pointvec.size(); i++){
            vertex = BRepBuilderAPI_MakeVertex(pointvec.at(i));
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());
        }

        myShapeVec.push_back(new AIS_Shape(aRes));
        myShapeVec.back()->SetColor(myColor);
        myShapeVec.back()->SetWidth(myWidth);
        myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);

        //! Reset.
        myPvec.clear();
        myMouseClick=0;
    }
}

//! Offsets a parallel point off a line in 2d.
//! side = offset -90 or 90 degrees.
//! p0 = line startpoint.
//! p1 = line endpoint.
//! mp = current mousepos. (desired offset distance).
gp_Pnt SketchControl::offset_point_from_line_xoy(bool side, gp_Pnt p0, gp_Pnt p1, double offset){
    gp_Pnt p3;
    double deg=0;
    if(!side){
        deg = -90;
    } else {
        deg=90;
    }

    double dx = p1.X() - p0.X();
    double dy = p1.Y() - p0.Y();

    double rotate_x1 = cos(deg * M_PI / 180.0 )* dx - sin(deg * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(deg * M_PI / 180.0 )* dx + cos(deg * M_PI / 180.0 ) * dy;

    //! p3 is rotated point p0.
    p3.SetX(p1.X()+rotate_x1);
    p3.SetY(p1.Y()+rotate_y1);

    //!  cross calculation
    //!    A-----------B------------C
    //! (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

    //! AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
    //! AC = 1000

    //! Xc = Xa + (AC * (Xb - Xa) / AB)
    //! Yc = Ya + (AC * (Yb - Ya) / AB)

    double Xa=p1.X();
    double Ya=p1.Y();
    double Xb=p3.X();
    double Yb=p3.Y();
    double AB=p1.Distance(p3);
    double AC=offset;

    double Xc = Xa + (AC * (Xb - Xa) / AB);
    double Yc = Ya + (AC * (Yb - Ya) / AB);

    p3.SetX(Xc);
    p3.SetY(Yc);

    return p3;
}

//! xoy=>yoz
gp_Pnt SketchControl::offset_point_from_line_yoz(bool side, gp_Pnt p0, gp_Pnt p1, double offset){
    gp_Pnt p3;
    double deg=0;
    if(!side){
        deg = -90;
    } else {
        deg=90;
    }

    double dx = p1.Y() - p0.Y();
    double dy = p1.Z() - p0.Z();

    double rotate_x1 = cos(deg * M_PI / 180.0 )* dx - sin(deg * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(deg * M_PI / 180.0 )* dx + cos(deg * M_PI / 180.0 ) * dy;

    //! p3 is rotated point p0.
    p3.SetY(p1.Y()+rotate_x1);
    p3.SetZ(p1.Z()+rotate_y1);

    //!  cross calculation
    //!    A-----------B------------C
    //! (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

    //! AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
    //! AC = 1000

    //! Xc = Xa + (AC * (Xb - Xa) / AB)
    //! Yc = Ya + (AC * (Yb - Ya) / AB)

    double Xa=p1.Y();
    double Ya=p1.Z();
    double Xb=p3.Y();
    double Yb=p3.Z();
    double AB=p1.Distance(p3);
    double AC=offset;

    double Xc = Xa + (AC * (Xb - Xa) / AB);
    double Yc = Ya + (AC * (Yb - Ya) / AB);

    p3.SetY(Xc);
    p3.SetZ(Yc);

    return p3;
}

//! xoy => zox
gp_Pnt SketchControl::offset_point_from_line_zox(bool side, gp_Pnt p0, gp_Pnt p1, double offset){
    gp_Pnt p3;
    double deg=0;
    if(!side){
        deg = -90;
    } else {
        deg=90;
    }

    double dx = p1.Z() - p0.Z();
    double dy = p1.X() - p0.X();

    double rotate_x1 = cos(deg * M_PI / 180.0 )* dx - sin(deg * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(deg * M_PI / 180.0 )* dx + cos(deg * M_PI / 180.0 ) * dy;

    //! p3 is rotated point p0.
    p3.SetZ(p1.Z()+rotate_x1);
    p3.SetX(p1.X()+rotate_y1);

    //!  cross calculation
    //!    A-----------B------------C
    //! (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

    //! AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
    //! AC = 1000

    //! Xc = Xa + (AC * (Xb - Xa) / AB)
    //! Yc = Ya + (AC * (Yb - Ya) / AB)

    double Xa=p1.Z();
    double Ya=p1.X();
    double Xb=p3.Z();
    double Yb=p3.X();
    double AB=p1.Distance(p3);
    double AC=offset;

    double Xc = Xa + (AC * (Xb - Xa) / AB);
    double Yc = Ya + (AC * (Yb - Ya) / AB);

    p3.SetZ(Xc);
    p3.SetX(Yc);

    return p3;
}

void SketchControl::OnMouseMoveEvent(bool finish)
{
    mp->SetPnt(mousedrawingpos);

    if(finish){
        myMouseClick++;
    }

    //! std::cout<<"mouse move x:"<<p.X()<<" y:"<<p.Y()<<" z:"<<p.Z()<<std::endl;

    myOrtho=ortho;
    double lx=0,ly=0,lz=0,x=0,y=0,z=0;

    switch(myPrimitiveType) {
    case none:
        break;
    case slot:
        //! First point.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());

            //! Preview a point.
            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberSlotPointA->SetShape(vertex);
            myContext->Display(myRubberSlotPointA,AIS_WireFrame,-1,Standard_True);

            myMouseClick=2;
        }
        //! Preview a line.
        if(myMouseClick==2){
            if(mp->Distance(p0)>0){
                myRubberLine->SetPoints(p0,mp);
                myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay(myRubberLine,Standard_True);
            }
        }
        //! Next point.
        if(myMouseClick==3){
            p1->SetPnt(mp->Pnt());

            //! Preview a point.
            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
            myRubberSlotPointB->SetShape(vertex);
            myContext->Display(myRubberSlotPointB,AIS_WireFrame,-1,Standard_True);

            myMouseClick=4;
        }
        //! Preview a shape with radius as next point
        if(myMouseClick==4){
            //! Radius point.
            p2->SetPnt(mp->Pnt());

            double radius=p2->Distance(p1);
            if(radius>0){
                //! Get the current sketch plane trough the myViewer.
                gp_Dir dir;
                //! Plane top.
                gp_Ax2 a=myViewer->PrivilegedPlane().Ax2();
                gp_Ax2 b=gp::XOY();
                if(b.Direction().X()==a.Direction().X() && b.Direction().Y()==a.Direction().Y() && b.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is XOY (top)"<<std::endl;
                    dir.SetXYZ({0,0,1});

                    //! Edge A of slot.
                    pa=offset_point_from_line_xoy(0,p0->Pnt(),p1->Pnt(),radius);
                    pb=offset_point_from_line_xoy(1,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeA->SetShape(BRepBuilderAPI_MakeEdge(pa,pb));

                    //! Edge B of slot.
                    pc=offset_point_from_line_xoy(1,p0->Pnt(),p1->Pnt(),radius);
                    pd=offset_point_from_line_xoy(0,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeB->SetShape(BRepBuilderAPI_MakeEdge(pc,pd));
                }
                //! Plane right.
                gp_Ax2 c=gp::YOZ();
                if(c.Direction().X()==a.Direction().X() && c.Direction().Y()==a.Direction().Y() && c.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is YOZ (right)"<<std::endl;
                    dir.SetXYZ({1,0,0});

                    //! Edge A of slot.
                    pa=offset_point_from_line_yoz(0,p0->Pnt(),p1->Pnt(),radius);
                    pb=offset_point_from_line_yoz(1,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeA->SetShape(BRepBuilderAPI_MakeEdge(pa,pb));

                    //! Edge B of slot.
                    pc=offset_point_from_line_yoz(1,p0->Pnt(),p1->Pnt(),radius);
                    pd=offset_point_from_line_yoz(0,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeB->SetShape(BRepBuilderAPI_MakeEdge(pc,pd));
                }
                //! Plane front.
                gp_Ax2 d=gp::ZOX();
                if(d.Direction().X()==a.Direction().X() && d.Direction().Y()==a.Direction().Y() && d.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is ZOX (front)"<<std::endl;
                    dir.SetXYZ({0,1,0});

                    //! Edge A of slot.
                    pa=offset_point_from_line_zox(0,p0->Pnt(),p1->Pnt(),radius);
                    pb=offset_point_from_line_zox(1,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeA->SetShape(BRepBuilderAPI_MakeEdge(pa,pb));

                    //! Edge B of slot.
                    pc=offset_point_from_line_zox(1,p0->Pnt(),p1->Pnt(),radius);
                    pd=offset_point_from_line_zox(0,p1->Pnt(),p0->Pnt(),radius);
                    myRubberSlotEdgeB->SetShape(BRepBuilderAPI_MakeEdge(pc,pd));
                }

                myContext->Display( myRubberSlotEdgeA,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay( myRubberSlotEdgeA,Standard_True);

                myContext->Display( myRubberSlotEdgeB,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay( myRubberSlotEdgeB,Standard_True);

                //! Arc A of slot.
                //! gp_Dir dir(0,0,1); //! Xoy.
                gp_Circ circleA(gp_Ax2(p0->Pnt(),dir),radius);
                Handle(Geom_TrimmedCurve) aArcOfCircle;
                aArcOfCircle = GC_MakeArcOfCircle(circleA,pd,pb,true);
                TopoDS_Edge aEdgeA = BRepBuilderAPI_MakeEdge(aArcOfCircle);
                myRubberSlotArcA->SetShape(aEdgeA);

                //! Arc B of slot.
                gp_Circ circleB(gp_Ax2(p1->Pnt(),dir),radius);
                aArcOfCircle = GC_MakeArcOfCircle(circleB,pa,pc,true);
                TopoDS_Edge aEdgeB = BRepBuilderAPI_MakeEdge(aArcOfCircle);
                myRubberSlotArcB->SetShape(aEdgeB);

                //! Display arc's.
                myContext->Display( myRubberSlotArcA,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay( myRubberSlotArcA,Standard_True);
                myContext->Display( myRubberSlotArcB,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay( myRubberSlotArcB,Standard_True);
            }
        }
        //! Draw the final shape.
        if(myMouseClick==5){
            myContext->Remove(myRubberLine,Standard_False);
            myContext->Remove(myRubberSlotEdgeA,Standard_False);
            myContext->Remove(myRubberSlotEdgeB,Standard_False);
            myContext->Remove(myRubberSlotArcA,Standard_False);
            myContext->Remove(myRubberSlotArcB,Standard_False);
            myContext->Remove(myRubberSlotPointA,Standard_False);
            myContext->Remove(myRubberSlotPointB,Standard_False);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, myRubberSlotEdgeA->Shape());
            aBuilder.Add (aRes, myRubberSlotEdgeB->Shape());
            aBuilder.Add (aRes, myRubberSlotArcA->Shape());
            aBuilder.Add (aRes, myRubberSlotArcB->Shape());
            aBuilder.Add (aRes, myRubberSlotPointA->Shape());
            aBuilder.Add (aRes, myRubberSlotPointB->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),Standard_True);

            //! Reset.
            myMouseClick=0;
        }

        break;
    case polygon:
        break;
    case bezier:

        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            p1->SetPnt(mp->Pnt());
            p2->SetPnt(mp->Pnt());
            p3->SetPnt(mp->Pnt());

            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }
        //! Preview as line.
        if(myMouseClick==2){
            if(mp->Distance(p0)>0){
                myRubberLine->SetPoints(p0,mp);
                myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay(myRubberLine,Standard_True);
            }
            p1->SetPnt(mp->Pnt());
            p2->SetPnt(mp->Pnt());
            p3->SetPnt(mp->Pnt());
        }

        if(myMouseClick==3){
            add_temp_point_to_preview(p1->Pnt());
            myMouseClick=4;
        }

        if(myMouseClick==4){
            myContext->Remove(myRubberLine,Standard_False);
            p2->SetPnt(mp->Pnt());
            p3->SetPnt(mp->Pnt());
        }

        if(myMouseClick==5){
             add_temp_point_to_preview(p2->Pnt());
            myMouseClick=6;
        }
        if(myMouseClick==6){
            p3->SetPnt(mp->Pnt());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p3->Pnt());
            myRubberPointVec.back()->SetShape(vertex);
        }

        if(myMouseClick>1){
            BRepBuilderAPI_MakeWire aWire;
            TopoDS_Edge aEdge;

            p4->SetPnt(p0->Pnt());

            int edgecount=0;
            for(double t=0; t<=1; t+=0.05){

                //! Cubic bezier curve. Mostly used for designing letter fonts etc.
                //! start point A..
                double Ax = p0->X();
                double Ay = p0->Y();
                double Az = p0->Z();

                //! control point B..
                double Bx = p1->X();
                double By = p1->Y();
                double Bz = p1->Z();

                //! control point C..
                double Cx = p2->X();
                double Cy = p2->Y();
                double Cz = p2->Z();

                //! end point D..
                double Dx = p3->X();
                double Dy = p3->Y();
                double Dz = p3->Z();

                //! at this stage we have defined all the points and de lines of the cubic bezier curve..
                //! Calculate Point E, on the line AB
                double Ex = ((1-t) * Ax) + (t * Bx);
                double Ey = ((1-t) * Ay) + (t * By);
                double Ez = ((1-t) * Az) + (t * Bz);

                //! Calculate Point F, on the line BC
                double Fx = ((1-t) * Bx) + (t * Cx);
                double Fy = ((1-t) * By) + (t * Cy);
                double Fz = ((1-t) * Bz) + (t * Cz);

                //! Calculate Point G, on the line CD
                double Gx = ((1-t) * Cx) + (t * Dx);
                double Gy = ((1-t) * Cy) + (t * Dy);
                double Gz = ((1-t) * Cz) + (t * Dz);

                //! Calculate Point Q, on the line EF
                double Qx = ((1-t) * Ex) + (t * Fx);
                double Qy = ((1-t) * Ey) + (t * Fy);
                double Qz = ((1-t) * Ez) + (t * Fz);

                //! Calculate Point R, on the line FG
                double Rx = ((1-t) * Fx) + (t * Gx);
                double Ry = ((1-t) * Fy) + (t * Gy);
                double Rz = ((1-t) * Fz) + (t * Gz);

                //! Calculate Point P, on the line QR
                double Px = ((1-t) * Qx) + (t * Rx);
                double Py = ((1-t) * Qy) + (t * Ry);
                double Pz = ((1-t) * Qz) + (t * Rz);

                gp_Pnt res;
                res.SetCoord(Px,Py,Pz);

                if(res.Distance(p4->Pnt())>0){
                    aEdge = BRepBuilderAPI_MakeEdge(p4->Pnt(),res);
                    aWire.Add(aEdge);
                    p4->SetPnt(res);
                    edgecount++;
                }
            }
            //! Absolute to last point.
            if(p4->Distance(p3)>0){
                aEdge = BRepBuilderAPI_MakeEdge(p4->Pnt(),p3->Pnt());
                aWire.Add(aEdge);
            }

            if(edgecount>1){
                //! Display the bezier curve.
                myRubberBezier->SetShape(aWire);
                myContext->Display(myRubberBezier,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                myContext->Redisplay(myRubberBezier,Standard_True);
            }
            //! Finish.
            if(myMouseClick==7){
                remove_all_temp_points();
                myContext->Remove(myRubberBezier,Standard_False);

                //! Building the Resulting Compound
                TopoDS_Compound aRes;
                BRep_Builder aBuilder;
                aBuilder.MakeCompound (aRes);
                aBuilder.Add (aRes, myRubberBezier->Shape());

                TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                vertex = BRepBuilderAPI_MakeVertex(p2->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                vertex = BRepBuilderAPI_MakeVertex(p3->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                myShapeVec.push_back(new AIS_Shape(aRes));
                myShapeVec.back()->SetColor(myColor);
                myShapeVec.back()->SetWidth(myWidth);

                myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);

                //! Reset.
                myMouseClick=0;
            }
        }

        break;
    case spline:
        if(myMouseClick==1){
            myPvec.clear();
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }
        if(myMouseClick==2){
            p1->SetPnt(mp->Pnt());

            myRubberLine->SetPoints(p0,p1);
            myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
            myContext->Redisplay(myRubberLine,Standard_True);
        }
        //! Display as spline.
        if(myMouseClick==3){
            myPvec.push_back(p0->Pnt());
            myPvec.push_back(p1->Pnt());
        }
        //! Odd
        if(myMouseClick>2 && myMouseClick%2!=0){
            myPvec.push_back(mp->Pnt());
            add_temp_point_to_preview(mp->Pnt());
            myMouseClick++;
        }
        //! Even is spline preview.
        if(myMouseClick>2 && myMouseClick%2==0 && myPvec.size()>2){
            myContext->Remove(myRubberLine,Standard_False);
            myPvec.back().SetXYZ({mp->X(),mp->Y(),mp->Z()});
            spline_preview(myPvec,0);
        }

        break;
    case arc_cp_3p:
        //! Arc centerpoint.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }
        //! Line preview to first arc circumfence point.
        if(myMouseClick==2){
            p1->SetPnt(mp->Pnt());
            if(p1->Distance(p0)>0){
                myRubberLine->SetPoints(p0,p1);
                myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay(myRubberLine,Standard_True);
            }
        }
        if(myMouseClick==3){
            add_temp_point_to_preview(p1->Pnt());
            myMouseClick=4;
        }
        //! Line preview to the second arc circumfence point.
        if(myMouseClick==4){
            p2->SetPnt(mp->Pnt());

            if(p2->Distance(p1)>0 && p1->Distance(p0)>0){
                myRubberLine->SetPoints(p0,p2);
                myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
                myContext->Redisplay(myRubberLine,Standard_True);
            }
        }

        //! Live preview wich side of the arc has to be kept.
        if(myMouseClick==5){
            myContext->Remove(myRubberLine,Standard_False);
            //! Let the user decide wich part of the arc to keep by hovering.
            int res=0;

            if(p2->Distance(p1)>0 && p1->Distance(p0)>0){

                //! Get the current sketch plane trough the myViewer.
                gp_Dir dir;
                //! Plane top.
                gp_Ax2 a=myViewer->PrivilegedPlane().Ax2();
                gp_Ax2 b=gp::XOY();
                if(b.Direction().X()==a.Direction().X() && b.Direction().Y()==a.Direction().Y() && b.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is XOY (top)"<<std::endl;
                    dir.SetXYZ({0,0,1});
                    res=side_of_line_xoy(p1->Pnt(),p2->Pnt(),mp->Pnt());
                }
                //! Plane right.
                gp_Ax2 c=gp::YOZ();
                if(c.Direction().X()==a.Direction().X() && c.Direction().Y()==a.Direction().Y() && c.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is YOZ (right)"<<std::endl;
                    dir.SetXYZ({1,0,0});
                    res=side_of_line_yoz(p1->Pnt(),p2->Pnt(),mp->Pnt());
                }
                //! Plane front.
                gp_Ax2 d=gp::ZOX();
                if(d.Direction().X()==a.Direction().X() && d.Direction().Y()==a.Direction().Y() && d.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is ZOX (front)"<<std::endl;
                    dir.SetXYZ({0,1,0});
                    res=side_of_line_zox(p1->Pnt(),p2->Pnt(),mp->Pnt());
                }

                gp_Circ circle(gp_Ax2(p0->Pnt(),dir),p0->Distance(p1));

                Handle(Geom_TrimmedCurve) aArcOfCircle;
                if(res>0){
                    aArcOfCircle = GC_MakeArcOfCircle(circle,p2->Pnt(),p1->Pnt(),true);
                    p3->SetPnt(aArcOfCircle->StartPoint());
                } else {
                    aArcOfCircle = GC_MakeArcOfCircle(circle,p1->Pnt(),p2->Pnt(),true);
                    p3->SetPnt(aArcOfCircle->EndPoint());
                }

                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);

                myRubberArc->SetShape(aEdge);
                myContext->Display(myRubberArc,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                myContext->Redisplay(myRubberArc,Standard_True);

            }
        }

        //! Create the final shape.
        if(myMouseClick==6){
            remove_all_temp_points();
            myContext->Remove(myRubberArc,Standard_False);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, myRubberArc->Shape());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(p3->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);
            myMouseClick=0;
        }
        break;

    case circle_3p:

        //! First point.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }
        //! Preview as line.
        if(myMouseClick==2){
            myRubberLine->SetPoints(p0,mp);
            myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
            myContext->Redisplay(myRubberLine,Standard_True);
        }

        //! Next point.
        if(myMouseClick==3){
            if(p1->Distance(p0)>0){
                p1->SetPnt(mp->Pnt());
                add_temp_point_to_preview(p1->Pnt());
                myMouseClick=4;
            } else {
                myMouseClick=2;
            }
        }

        //! Live preview 3th point.
        if(myMouseClick==4){
            if(mp->Distance(p1)>0){
                myContext->Remove(myRubberLine,Standard_False);
                Handle(Geom_Circle) aCircle  = GC_MakeCircle(p0->Pnt(),p1->Pnt(),mp->Pnt());
                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aCircle);
                myRubberCircle->SetShape(aEdge);
                myContext->Display(myRubberCircle,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                myContext->Redisplay(myRubberCircle,Standard_True);
            }
        }
        //! Final shape.
        if(myMouseClick==5){
            remove_all_temp_points();
            myContext->Remove(myRubberCircle,Standard_False);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, myRubberCircle->Shape());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(mp->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            //! Calculate centerpoint of the 3p 3d circle.
            arccenter().circlecenter3d(p0->Pnt(),p1->Pnt(),mp->Pnt(),cp,myDummy,myDummy);
            vertex = BRepBuilderAPI_MakeVertex(cp);
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);
            //! Reset.
            myMouseClick=0;
        }
        break;
    case circle_cp_2p:
        //! Circle centerpoint.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }
        //! Circle live preview.
        if(myMouseClick==2){

            double radius=p0->Pnt().Distance(mp->Pnt());
            if(radius>0){

                //! Get the current sketch plane trough the myViewer.
                gp_Dir dir;
                //! Plane top.
                gp_Ax2 a=myViewer->PrivilegedPlane().Ax2();
                gp_Ax2 b=gp::XOY();
                if(b.Direction().X()==a.Direction().X() && b.Direction().Y()==a.Direction().Y() && b.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is XOY (top)"<<std::endl;
                    dir.SetXYZ({0,0,1});
                }

                //! Plane right.
                gp_Ax2 c=gp::YOZ();
                if(c.Direction().X()==a.Direction().X() && c.Direction().Y()==a.Direction().Y() && c.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is YOZ (right)"<<std::endl;
                    dir.SetXYZ({1,0,0});
                }

                //! Plane front.
                gp_Ax2 d=gp::ZOX();
                if(d.Direction().X()==a.Direction().X() && d.Direction().Y()==a.Direction().Y() && d.Direction().Z()==a.Direction().Z()){
                    std::cout<<"direction is ZOX (front)"<<std::endl;
                    dir.SetXYZ({0,1,0});
                }

                gp_Circ circle(gp_Ax2(p0->Pnt(),dir),radius);
                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(circle);
                myRubberCircle->SetShape(aEdge);
                myContext->Display(myRubberCircle,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                myContext->Redisplay(myRubberCircle,Standard_True);
            }
        }

        //! Create final shape
        if(myMouseClick==3){
            remove_all_temp_points();
            myContext->Remove(myRubberCircle,Standard_False);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, myRubberCircle->Shape());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(mp->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);
            //! Reset.
            myMouseClick=0;

        }

        break;
    case square:

        //! a Click.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            p1->SetPnt(mp->Pnt());
            p2->SetPnt(mp->Pnt());
            p3->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }

        //! Live preview.
        if(myMouseClick==2){

            //! Get the current sketch plane trough the myViewer.
            //!
            //! Plane top.
            gp_Ax2 a=myViewer->PrivilegedPlane().Ax2();
            gp_Ax2 b=gp::XOY();
            if(b.Direction().X()==a.Direction().X() && b.Direction().Y()==a.Direction().Y() && b.Direction().Z()==a.Direction().Z()){
                std::cout<<"direction is XOY (top)"<<std::endl;
                p1->SetY(mp->Y());
                p2->SetX(mp->X());
                p2->SetY(mp->Y());
                p3->SetX(mp->X());
            }

            //! Plane right.
            gp_Ax2 c=gp::YOZ();
            if(c.Direction().X()==a.Direction().X() && c.Direction().Y()==a.Direction().Y() && c.Direction().Z()==a.Direction().Z()){
                std::cout<<"direction is YOZ (right)"<<std::endl;
                p1->SetZ(mp->Z());
                p2->SetY(mp->Y());
                p2->SetZ(mp->Z());
                p3->SetY(mp->Y());
            }

            //! Plane front.
            gp_Ax2 d=gp::ZOX();
            if(d.Direction().X()==a.Direction().X() && d.Direction().Y()==a.Direction().Y() && d.Direction().Z()==a.Direction().Z()){
                std::cout<<"direction is ZOX (front)"<<std::endl;
                p1->SetZ(mp->Z());
                p2->SetX(mp->X());
                p2->SetZ(mp->Z());
                p3->SetX(mp->X());
            }

            //! Construct a square.
            TopoDS_Edge aEdge;
            BRepBuilderAPI_MakeWire aWire;
            if(p0->Distance(p1)>0){
                aEdge = BRepBuilderAPI_MakeEdge(p0->Pnt(),p1->Pnt());
                aWire.Add(aEdge);
                if(p1->Distance(p2)>0){
                    aEdge = BRepBuilderAPI_MakeEdge(p1->Pnt(),p2->Pnt());
                    aWire.Add(aEdge);
                    if(p2->Distance(p3)>0){
                        aEdge = BRepBuilderAPI_MakeEdge(p2->Pnt(),p3->Pnt());
                        aWire.Add(aEdge);
                        if(p3->Distance(p0)>0){
                            aEdge = BRepBuilderAPI_MakeEdge(p3->Pnt(),p0->Pnt());
                            aWire.Add(aEdge);

                            myRubberSquare->SetShape(aWire);
                            myContext->Display(myRubberSquare,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                            myContext->Redisplay(myRubberSquare,Standard_True);
                            myWire=aWire;
                        }
                    }
                }
            }

        }

        //! Create the final shape.
        if(myMouseClick==3){
            remove_all_temp_points();
            myContext->Remove(myRubberSquare,Standard_False);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, myRubberSquare->Shape());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(mp->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);
            //! Reset.
            myMouseClick=0;
        }
        break;
    case point:

        if(myMouseClick==1){
            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(mp->Pnt());
            //! Handle(AIS_Shape) aShape= new AIS_Shape(vertex);
            myShapeVec.push_back(new AIS_Shape(vertex));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),Standard_True);
            //! Reset.
            myMouseClick=0;
        }
        break;
    case line:
goto_line:

        //! a Click.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myRubberLine->SetPoints(p0,p1);
            myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
            myMouseClick=2;
        }

        //! 3d Ortho implementation.
        if(ortho && myMouseClick>=2){
            lx=sqrt(pow(mp->X()-p0->X(),2));
            ly=sqrt(pow(mp->Y()-p0->Y(),2));
            lz=sqrt(pow(mp->Z()-p0->Z(),2));
            if(lx>=ly && lx>lz){
                mp->SetY(p0->Y());
                mp->SetZ(p0->Z());
                x=mp->X()-p0->X();
                show_LineEdit(true,Focus::xaxis,{x,y,z});
            } else
                if(ly>=lx && ly>lz){
                    mp->SetX(p0->X());
                    mp->SetZ(p0->Z());
                    y=mp->Y()-p0->Y();
                    show_LineEdit(true,Focus::yaxis,{x,y,z});
                } else {
                    //if (lz>=lx && lz>ly){
                    mp->SetX(p0->X());
                    mp->SetY(p0->Y());
                    z=mp->Z()-p0->Z();
                    show_LineEdit(true,Focus::zaxis,{x,y,z});
                }
        }

        if(!ortho){
            show_LineEdit(false,Focus::none,mp->Pnt());
        }

        //! Live preview.
        if(myMouseClick==2){
            if(mp->Distance(p0)>0){
                p1->SetPnt(mp->Pnt());
                myRubberLine->SetPoints(p0,p1);
                myContext->Redisplay(myRubberLine,Standard_True);
            }
        }

        //! Create the final shape.
        if(myMouseClick==3){
            if(mp->Distance(p0)>0){

                p1->SetPnt(mp->Pnt());
                remove_all_temp_points();

                TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p0->Pnt(),p1->Pnt());
                Handle(AIS_Shape) aShape= new AIS_Shape(edge);

                //! Building the Resulting Compound
                TopoDS_Compound aRes;
                BRep_Builder aBuilder;
                aBuilder.MakeCompound (aRes);
                aBuilder.Add (aRes, aShape->Shape());

                TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
                myRubberPoint->SetShape(vertex);
                aBuilder.Add (aRes, myRubberPoint->Shape());

                myShapeVec.push_back(new AIS_Shape(aRes));
                myShapeVec.back()->SetColor(myColor);
                myShapeVec.back()->SetWidth(myWidth);
                myContext->Display(myShapeVec.back(),Standard_True);

                aShape.Nullify();

                //! Function repeat.
                p0->SetPnt(p1->Pnt());
                myMouseClick=2;
            }
        }
        break;
    case linestrip:
        goto goto_line;
        break;
    case arc_3p:

        //! Arc startpoint.
        if(myMouseClick==1){
            p0->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p0->Pnt());
            myMouseClick=2;
        }

        //! Live preview as line to arc controlpoint.
        if(myMouseClick==2){
            p1->SetPnt(mp->Pnt());
            myRubberLine->SetPoints(p0,p1);
            myContext->Display(myRubberLine,AIS_WireFrame,-1,Standard_False);
            myContext->Redisplay(myRubberLine,Standard_True);
        }

        //! Arc controlpoint.
        if(myMouseClick==3){
            p1->SetPnt(mp->Pnt());
            add_temp_point_to_preview(p1->Pnt());
            myMouseClick=4;
        }

        //! Live arc preview to endpoint.
        if(myMouseClick==4){
            p2->SetPnt(mp->Pnt());
            if(p1->Distance(p2)>0){
                myContext->Remove(myRubberLine,Standard_False);
                Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p0->Pnt(),p1->Pnt(),p2->Pnt());
                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
                myRubberArc->SetShape(aEdge);
                myContext->Display(myRubberArc,AIS_WireFrame,-1,Standard_False); //! No selection at hovering.
                myContext->Redisplay(myRubberArc,Standard_True);
            }
        }

        //! Arc endpoint.
        if(myMouseClick==5){
            p2->SetPnt(mp->Pnt());
            remove_all_temp_points();
            myContext->Remove(myRubberArc,Standard_False);

            Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p0->Pnt(),p1->Pnt(),p2->Pnt());
            TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
            Handle(AIS_Shape) aShape= new AIS_Shape(aEdge);

            //! Building the Resulting Compound
            TopoDS_Compound aRes;
            BRep_Builder aBuilder;
            aBuilder.MakeCompound (aRes);
            aBuilder.Add (aRes, aShape->Shape());

            TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(p0->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(p1->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            vertex = BRepBuilderAPI_MakeVertex(p2->Pnt());
            myRubberPoint->SetShape(vertex);
            aBuilder.Add (aRes, myRubberPoint->Shape());

            myShapeVec.push_back(new AIS_Shape(aRes));
            myShapeVec.back()->SetColor(myColor);
            myShapeVec.back()->SetWidth(myWidth);
            myContext->Display(myShapeVec.back(),AIS_WireFrame,0,Standard_True);

            //! Reset.
            aShape.Nullify();
            myMouseClick=0;
        }

        break;
    default:
        break;
    }
}























