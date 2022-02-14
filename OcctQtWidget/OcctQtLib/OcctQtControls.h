#ifndef OCCTQTCONTROLS_H
#define OCCTQTCONTROLS_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QSlider>
#include <gp_Pnt.hxx>


namespace Ui {
class OcctQtControls;
}

class OcctQtControls : public QWidget
{
    Q_OBJECT

public:
    explicit OcctQtControls(QWidget *parent = nullptr);
    ~OcctQtControls();

    void update_labels(gp_Pnt p);
    void set_snap_checked(bool state);
    void set_ortho_checked(bool state);

    QToolButton *tlb_snap, *tlb_ortho;

signals:
    void toolButton_zoom_3d_pressed();
    void toolButton_zoom_back_pressed();
    void toolButton_zoom_bottom_pressed();
    void toolButton_zoom_front_pressed();
    void toolButton_zoom_left_pressed();
    void toolButton_zoom_right_pressed();
    void toolButton_zoom_top_pressed();
    void toolButton_zoom_extends_pressed();
    void toolButton_zoom_plus_pressed();
    void toolButton_zoom_min_pressed();
    void verticalSlider_sliderMoved(int position);
    void toolButton_settings_pressed();
    void toolButton_open_filecenter_pressed();

    void toolButton_draw_cancel_pressed();
    void toolButton_draw_2p_line_pressed();
    void toolButton_draw_3p_arc_pressed();
    void toolButton_draw_2p_circle_pressed();
    void toolButton_draw_point_pressed();
    void toolButton_draw_3p_circle_pressed();
    void toolButton_draw_3p_cp_arc_pressed();
    void toolButton_draw_3p_tan_circle_pressed();
    void toolButton_draw_2p_tan_circle_pressed();
    void toolButton_draw_bspline_pressed();
    void toolButton_draw_bezier_pressed();

    void toolButton_snap_end_pressed();
    void toolButton_snap_center_pressed();
    void toolButton_snap_mid_pressed();
    void toolButton_snap_perpendicular_pressed();
    void toolButton_snap_intersection_pressed();
    void toolButton_snap_tangent_pressed();
    void toolButton_snap_nearest_pressed();

    void toolButton_snap_parallel_pressed();
    void toolButton_snap_on_toggled(bool checked);

    void toolButton_trim_pressed();
    void toolButton_erase_pressed();

    void toolButton_plane_front_pressed();
    void toolButton_plane_top_pressed();
    void toolButton_plane_right_pressed();

    void toolButton_sketch_color_pressed();

    void F3(bool checked);
    void F8(bool checked);

private slots:
    void on_toolButton_zoom_3d_pressed();
    void on_toolButton_zoom_back_pressed();
    void on_toolButton_zoom_bottom_pressed();
    void on_toolButton_zoom_front_pressed();
    void on_toolButton_zoom_left_pressed();
    void on_toolButton_zoom_right_pressed();
    void on_toolButton_zoom_top_pressed();
    void on_toolButton_zoom_extends_pressed();
    void on_toolButton_zoom_plus_pressed();
    void on_toolButton_zoom_min_pressed();
    void on_verticalSlider_sliderMoved(int position);
    void on_toolButton_settings_pressed();
    void on_toolButton_open_filecenter_pressed();
    void on_toolButton_draw_2p_line_pressed();
    void on_toolButton_draw_3p_arc_pressed();
    void on_toolButton_draw_2p_circle_pressed();
    void on_toolButton_ortho_toggled(bool checked);
    void on_toolButton_snap_toggled(bool checked);

    void on_toolButton_draw_cancel_pressed();
    void on_toolButton_draw_point_pressed();
    void on_toolButton_draw_3p_circle_pressed();
    void on_toolButton_draw_3p_cp_arc_pressed();

    void on_toolButton_snap_end_pressed();
    void on_toolButton_snap_center_pressed();
    void on_toolButton_snap_mid_pressed();
    void on_toolButton_snap_perpendicular_pressed();
    void on_toolButton_snap_intersection_pressed();
    void on_toolButton_snap_tangent_pressed();
    void on_toolButton_snap_nearest_pressed();
    void on_toolButton_snap_parallel_pressed();
    void on_toolButton_snap_on_toggled(bool checked);
    void on_toolButton_draw_3p_tan_circle_pressed();
    void on_toolButton_draw_2p_tan_circle_pressed();
    void on_toolButton_draw_bspline_pressed();
    void on_toolButton_draw_bezier_pressed();

    void on_toolButton_trim_pressed();
    void on_toolButton_erase_pressed();

    void on_toolButton_plane_front_pressed();
    void on_toolButton_plane_top_pressed();
    void on_toolButton_plane_right_pressed();

    void on_toolButton_sketch_color_pressed();

private:
    Ui::OcctQtControls *ui;
};

#endif // OCCTQTCONTROLS_H
