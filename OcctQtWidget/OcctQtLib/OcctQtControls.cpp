#include "OcctQtControls.h"
#include "ui_OcctQtControls.h"
#include <iostream>

//! Creating control pointers to be used in a upper class.
OcctQtControls::OcctQtControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcctQtControls)
{
    ui->setupUi(this);

    setMouseTracking(true);
}

//! Destructor.
OcctQtControls::~OcctQtControls()
{
    delete ui;
}

//! Signals and slots.
void OcctQtControls::on_toolButton_zoom_3d_pressed()
{
    //! The signals.
    toolButton_zoom_3d_pressed();
}

void OcctQtControls::update_labels(gp_Pnt p){
    ui->label_val_mouse_x->setText(QString::number(p.X(),'f',3));
    ui->label_val_mouse_y->setText(QString::number(p.Y(),'f',3));
    ui->label_val_mouse_z->setText(QString::number(p.Z(),'f',3));
}

void OcctQtControls::on_toolButton_zoom_back_pressed()
{
    toolButton_zoom_back_pressed();
}

void OcctQtControls::on_toolButton_zoom_bottom_pressed()
{
    toolButton_zoom_bottom_pressed();
}

void OcctQtControls::on_toolButton_zoom_front_pressed()
{
    toolButton_zoom_front_pressed();
}

void OcctQtControls::on_toolButton_zoom_left_pressed()
{
    toolButton_zoom_left_pressed();
}

void OcctQtControls::on_toolButton_zoom_right_pressed()
{
    toolButton_zoom_right_pressed();
}

void OcctQtControls::on_toolButton_zoom_top_pressed()
{
    toolButton_zoom_top_pressed();
}

void OcctQtControls::on_toolButton_zoom_extends_pressed()
{
    toolButton_zoom_extends_pressed();
}

void OcctQtControls::on_toolButton_zoom_plus_pressed()
{
    toolButton_zoom_plus_pressed();
}

void OcctQtControls::on_toolButton_zoom_min_pressed()
{
    toolButton_zoom_min_pressed();
}

void OcctQtControls::on_verticalSlider_sliderMoved(int position)
{
    verticalSlider_sliderMoved(position);
}

void OcctQtControls::on_comboBox_currentIndexChanged(int index)
{
    comboBox_currentIndexChanged(index);
}
