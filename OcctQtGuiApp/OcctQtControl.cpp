#include "OcctQtControl.h"
#include "ui_OcctQtControl.h"

#include "Interface.h"

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

void OcctQtControl::on_pushButton_line_pressed()
{
    OBJECT *line = new OBJECT();
    line->setType(TYPE::line);
    line->setPoints({{0,10,0},{10,10,0}});

    OBJECT *line2 = new OBJECT();
    line2->setType(TYPE::line);
    line2->setPoints({{0,0,0},{10,0,0}});

    std::vector<gp_Pnt> pvec;
    bool ok=line->getIntersections(*line2, pvec);
    if(ok){
        std::cout<<"intersection p.x:"<<pvec[0].X()<<" p.y:"<<pvec[0].Y()<<" p.z:"<<pvec[0].Z()<<std::endl;
    } else {
        std::cout<<"no intersection found"<<std::endl;
    }
}

void OcctQtControl::on_pushButton_circle_pressed()
{
    OBJECT *line = new OBJECT();
    line->setType(TYPE::line);
    line->setPoints({{50,0,0},{50,100,0}});

    OBJECT *arc = new OBJECT();
    arc->setType(TYPE::arc_3p);
    arc->setPoints({{0,0,0},{50,50,0},{100,0,0}});
    arc->setRadius(50);

    std::vector<gp_Pnt> pvec;
    std::setprecision(3);
    bool ok=line->getIntersections(*arc, pvec);
    if(ok){
        for(unsigned int i=0; i<pvec.size(); i++){
            std::cout<<std::fixed<<"intersection at p.x:"<<pvec[i].X()<<" p.y:"<<pvec[i].Y()<<" p.z:"<<pvec[i].Z()<<std::endl;
        }
    } else {
        std::cout<<"no intersection found"<<std::endl;
    }

    std::vector<gp_Pnt> pointvec=ArcPoints({0,0,0},{50,50,0},{100,0,0}).getPoints(50);
    for(unsigned int i=0; i<pointvec.size(); i++){
        std::cout<<"intersection at p.x:"<<pointvec[i].X()<<" p.y:"<<pointvec[i].Y()<<" p.z:"<<pointvec[i].Z()<<std::endl;
    }
}




















