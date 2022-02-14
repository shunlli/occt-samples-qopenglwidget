#ifndef OCCTQTWIDGET_H
#define OCCTQTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <QToolButton>
#include <QLabel>
#include <QFileDialog>
#include <QColorDialog>
#include <QPair>
#include <OcctQtViewer.h>
#include <OcctQtControls.h>
#include <OcctQtMenu.h>
#include <OcctQtFunctions.h>
#include <OcctQtFile.h>

namespace Ui {
class OcctQtWidget;
}

class OcctQtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OcctQtWidget(QWidget *parent = nullptr);
    ~OcctQtWidget();

    void set_mousepos();
    void set_backgroundcolor(QColor color);

    struct STEPFILE{
        QString filename;
        std::vector<Handle(AIS_Shape)> shapevec;
    };
    std::vector<STEPFILE> stepfilevec;

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
    void on_checkBox_orthograpic_pressed();
    void on_checkBox_perspective_pressed();
    void on_checkBox_navi_cube_show_pressed();
    void on_checkBox_navi_cube_hide_pressed();
    void on_checkBox_triedron_show_pressed();
    void on_checkBox_triedron_hide_pressed();
    void on_checkBox_boundary_show_pressed();
    void on_checkBox_boundary_hide_pressed();
    void on_checkBox_shaded_pressed();
    void on_checkBox_wireframe_pressed();

    void on_toolButton_open_filecenter_pressed();

    void on_toolButton_open_document_pressed(QPair<QString,QString> data);
    void on_toolButton_close_document_pressed(QString str);
    void on_toolButton_save_document_pressed(QPair<QString,QString> data);

    void on_toolButton_draw_cancel_pressed();
    void on_toolButton_draw_2p_line_pressed();
    void on_toolButton_draw_3p_arc_pressed();
    void on_toolButton_draw_3p_cp_arc_pressed();
    void on_toolButton_draw_2p_circle_pressed();
    void on_toolButton_draw_3p_circle_pressed();
    void on_toolButton_draw_point_pressed();
    void on_toolButton_draw_2p_tan_circle_pressed();
    void on_toolButton_draw_3p_tan_circle_pressed();
    void on_toolButton_draw_bspline_pressed();
    void on_toolButton_draw_bezier_pressed();

    void on_toolButton_trim_pressed();
    void on_toolButton_erase_pressed();
    void on_toolButton_sketch_color_pressed();

    void on_toolButton_snap_end_pressed();
    void on_toolButton_snap_mid_pressed();
    void on_toolButton_snap_center_pressed();
    void on_toolButton_snap_perpendicular_pressed();
    void on_toolButton_snap_intersection_pressed();
    void on_toolButton_snap_tangent_pressed();
    void on_toolButton_snap_nearest_pressed();
    void on_toolButton_snap_parallel_pressed();
    void on_toolButton_snap_on_toggled(bool checked);

    void on_toolButton_plane_front_pressed();
    void on_toolButton_plane_right_pressed();
    void on_toolButton_plane_top_pressed();

    void on_F3(bool checked);
    void on_F8(bool checked);

private:
    //! Load a stepfile. A stepfile can contain multiple shapes.
    std::vector<Handle(AIS_Shape)> load_stepfile(QString filename);

private:
    Ui::OcctQtWidget *ui;

    OcctQtViewer *occt_viewer=new OcctQtViewer();
    OcctQtControls *occt_controls=new OcctQtControls();
    OcctQtMenu *occt_menu = new OcctQtMenu();
    OcctQtFunctions *occt_functions= new OcctQtFunctions();
    OcctQtFile *occt_file = new OcctQtFile();
};

#endif // OCCTQTWIDGET_H
