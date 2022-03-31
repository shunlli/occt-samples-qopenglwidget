#ifndef SKETCHCONTROL_H
#define SKETCHCONTROL_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDialog>
#include <QLineEdit>
#include <QPair>
#include <QGridLayout>
#include <iostream>
#include <OcctQtCommon.h>

#include <gp_Pnt.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>
#include <AIS_Line.hxx>
#include <AIS_Circle.hxx>
#include <AIS_Shape.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Plane.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#include "arccenter.h"

class SketchControl : public QWidget
{
    Q_OBJECT
public:
    SketchControl(Handle(AIS_InteractiveContext)& theContext, Handle(V3d_Viewer)& theViewer);

    enum PrimitiveType{
        none,
        point,
        line,
        linestrip,
        square,
        polygon,        //! Todo.
        slot,
        arc_3p,
        arc_cp_3p,
        circle_3p,
        circle_cp_2p,
        bezier,
        spline,
    };

    std::vector<Handle(AIS_Shape)> myShapeVec;

    void OnMouseMoveEvent( bool finish);
    void SetPrimitiveType(enum PrimitiveType thePrimimitveType);
    void Cancel();
    void SetColor(const Quantity_NameOfColor theColor);
    int side_of_line_xoy(gp_Pnt a, gp_Pnt b, gp_Pnt c);
    int side_of_line_yoz(gp_Pnt a, gp_Pnt b, gp_Pnt c);
    int side_of_line_zox(gp_Pnt a, gp_Pnt b, gp_Pnt c);
    void spline_preview(std::vector<gp_Pnt> pointvec, bool set_final_shape);
    gp_Pnt offset_point_from_line_xoy(bool side, gp_Pnt p0, gp_Pnt p1, double offset);
    gp_Pnt offset_point_from_line_yoz(bool side, gp_Pnt p0, gp_Pnt p1, double offset);
    gp_Pnt offset_point_from_line_zox(bool side, gp_Pnt p0, gp_Pnt p1, double offset);
    void add_temp_point_to_preview(gp_Pnt p);
    void remove_all_temp_points();

signals:
    void show_LineEdit(bool arg, Focus f, gp_Pnt p);

public slots:
    void on_lineEdit_returnPressed(gp_Pnt p);

private:

    int myMouseClick=0;
    bool myOrtho=0;
    double myValue=0, myDummy=0;
    bool oneshot=0;
    QDialog *Dialog=new QDialog();
    QGridLayout *Gridlayout=new QGridLayout();
    QLineEdit *LinEedit=new QLineEdit();


    PrimitiveType myPrimitiveType;

    BRepBuilderAPI_MakeWire                     myWire;

    Handle(V3d_Viewer)                          myViewer;
    Handle(AIS_InteractiveContext)              myContext;
    Handle(AIS_Line)                            myRubberLine;
    Handle(AIS_Shape)                           myRubberPoint;
    std::vector< Handle(AIS_Shape)>             myRubberPointVec;
    Handle(AIS_Shape)                           myRubberSquare;
    Handle(AIS_Shape)                           myRubberArc;
    Handle(AIS_Shape)                           myRubberCircle;
    Handle(AIS_Shape)                           myRubberSpline;
    Handle(AIS_Shape)                           myRubberBezier;

    Handle(AIS_Shape)                           myRubberSlotArcA;
    Handle(AIS_Shape)                           myRubberSlotArcB;
    Handle(AIS_Shape)                           myRubberSlotEdgeA;
    Handle(AIS_Shape)                           myRubberSlotEdgeB;
    Handle(AIS_Shape)                           myRubberSlotPointA;
    Handle(AIS_Shape)                           myRubberSlotPointB;
    gp_Pnt                                      pa,pb,pc,pd,cp;

    Handle(Geom_CartesianPoint)                 p0,p1,p2,p3,p4,mp;

    std::vector<gp_Pnt>                         myPvec;
    Quantity_NameOfColor                        myColor;
    unsigned int                                myWidth=2;
   // std::vector<Handle(Geom_CartesianPoint)>    control;
};

#endif // SKETCHCONTROL_H
