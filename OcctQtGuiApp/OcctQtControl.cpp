#include "OcctQtControl.h"
#include "ui_OcctQtControl.h"

OcctQtControl::OcctQtControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OcctQtControl)
{
    ui->setupUi(this);

    setMouseTracking(true);
    lbl_x= ui->label_val_mouse_x;
    lbl_y= ui->label_val_mouse_y;
    lbl_z= ui->label_val_mouse_z;

    btn_zoom_top=ui->toolButton_zoom_top;
    btn_zoom_bottom=ui->toolButton_zoom_bottom;
    btn_zoom_front=ui->toolButton_zoom_fromt;
    btn_zoom_back=ui->toolButton_zoom_back;
    btn_zoom_left=ui->toolButton_zoom_left;
    btn_zoom_right=ui->toolButton_zoom_right;
    btn_zoom_extends=ui->toolButton_zoom_extends;
    btn_zoom_plus=ui->toolButton_zoom_plus;
    btn_zoom_min=ui->toolButton_zoom_min;
    btn_zoom_3d=ui->toolButton_zoom_3d;
}

OcctQtControl::~OcctQtControl()
{
    delete ui;
}

#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <gp_Pnt.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <ElCLib.hxx>

void OcctQtControl::on_pushButton_line_pressed()
{
    //! The line example :
    gp_Pnt a{0,0,0};
    gp_Pnt b{100,100,0};
    double linelenght=a.Distance(b);
    std::cout<<"linelenght:"<<linelenght<<std::endl;

    //! A non normalized line direction :
    gp_Dir dir(b.X()-a.X(), b.Y()-a.Y(), b.Z()-a.Z());

    //! Question is : how to calculate the "param" from given position.
    //!
    //! Input position : x50, y50, z50.
    //! Output

    gp_Pnt givenpos(50,50,0);
    const gp_Ax1 Axis(a,dir);
    double param=ElCLib::LineParameter(Axis,givenpos);

    std::cout<<"param:"<<param<<std::endl;
}

void OcctQtControl::on_pushButton_circle_pressed()
{
    //! The arc example :
    gp_Pnt start{0,0,0};
    gp_Pnt end{100,100,0};
    gp_Pnt center{50,0,0};

    gp_Ax2 PlaneTop=gp::XOY();
    PlaneTop.SetLocation(center);

    gp_Pnt givenleftpos(0,0,0);
    double param=ElCLib::CircleParameter(PlaneTop,givenleftpos);
    std::cout<<"leftpos param in radians:"<<param<<std::endl;

    gp_Pnt givenrightpos(100,0,0);
    param=ElCLib::CircleParameter(PlaneTop,givenrightpos);
    std::cout<<"rightpos param in radians:"<<param<<std::endl;



}




















