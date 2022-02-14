#include "OcctQtControls.h"
#include "ui_OcctQtControls.h"
#include <iostream>
#include <QMenu>



//! Creating control pointers to be used in a upper class.
OcctQtControls::OcctQtControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcctQtControls)
{
    ui->setupUi(this);
    setMouseTracking(true);
    tlb_ortho=ui->toolButton_ortho;
    tlb_snap=ui->toolButton_snap;
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

void OcctQtControls::on_toolButton_settings_pressed()
{
    toolButton_settings_pressed();
}

void OcctQtControls::on_toolButton_open_filecenter_pressed()
{
    toolButton_open_filecenter_pressed();
}

void OcctQtControls::on_toolButton_draw_2p_line_pressed()
{
    toolButton_draw_2p_line_pressed();
}

void OcctQtControls::on_toolButton_draw_3p_arc_pressed()
{
    toolButton_draw_3p_arc_pressed();
}

void OcctQtControls::on_toolButton_draw_2p_circle_pressed()
{
    toolButton_draw_2p_circle_pressed();
}

void OcctQtControls::on_toolButton_ortho_toggled(bool checked)
{
     F8(checked);
}

void OcctQtControls::on_toolButton_snap_toggled(bool checked)
{
    F3(checked);
}

void OcctQtControls::on_toolButton_draw_point_pressed()
{
    toolButton_draw_point_pressed();
}

void OcctQtControls::on_toolButton_draw_3p_circle_pressed()
{
    toolButton_draw_3p_circle_pressed();
}

void OcctQtControls::on_toolButton_draw_3p_cp_arc_pressed()
{
    toolButton_draw_3p_cp_arc_pressed();
}

void OcctQtControls::on_toolButton_snap_end_pressed()
{
    toolButton_snap_end_pressed();
}

void OcctQtControls::on_toolButton_snap_center_pressed()
{
    toolButton_snap_center_pressed();
}

void OcctQtControls::on_toolButton_snap_mid_pressed()
{
    toolButton_snap_mid_pressed();
}

void OcctQtControls::on_toolButton_snap_perpendicular_pressed()
{
    toolButton_snap_perpendicular_pressed();
}

void OcctQtControls::on_toolButton_snap_intersection_pressed()
{
    toolButton_snap_intersection_pressed();
}

void OcctQtControls::on_toolButton_snap_tangent_pressed()
{
    toolButton_snap_tangent_pressed();
}

void OcctQtControls::on_toolButton_snap_nearest_pressed()
{
    toolButton_snap_nearest_pressed();
}

void OcctQtControls::on_toolButton_snap_parallel_pressed()
{
    toolButton_snap_parallel_pressed();
}

void OcctQtControls::on_toolButton_snap_on_toggled(bool checked)
{
    toolButton_snap_on_toggled(checked);
}

void OcctQtControls::on_toolButton_draw_3p_tan_circle_pressed()
{
    toolButton_draw_3p_tan_circle_pressed();
}

void OcctQtControls::on_toolButton_draw_2p_tan_circle_pressed()
{
    toolButton_draw_2p_tan_circle_pressed();
}

void OcctQtControls::on_toolButton_draw_bspline_pressed()
{
    toolButton_draw_bspline_pressed();
}

void OcctQtControls::on_toolButton_draw_bezier_pressed()
{
    toolButton_draw_bezier_pressed();
}

void OcctQtControls::on_toolButton_trim_pressed()
{
    toolButton_trim_pressed();
}

void OcctQtControls::on_toolButton_erase_pressed()
{
    toolButton_erase_pressed();
}

void OcctQtControls::on_toolButton_plane_front_pressed()
{
    toolButton_plane_front_pressed();
}

void OcctQtControls::on_toolButton_plane_top_pressed()
{
    toolButton_plane_top_pressed();
}

void OcctQtControls::on_toolButton_plane_right_pressed()
{
    toolButton_plane_right_pressed();
}

void OcctQtControls::on_toolButton_draw_cancel_pressed()
{
     toolButton_draw_cancel_pressed();
}

void OcctQtControls::on_toolButton_sketch_color_pressed()
{
    toolButton_sketch_color_pressed();
}
