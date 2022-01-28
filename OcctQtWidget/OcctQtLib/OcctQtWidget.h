#ifndef OCCTQTWIDGET_H
#define OCCTQTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <QToolButton>
#include <QLabel>
#include <OcctQtViewer.h>
#include <OcctQtControls.h>

namespace Ui {
class OcctQtWidget;
}

class OcctQtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OcctQtWidget(QWidget *parent = nullptr);
    ~OcctQtWidget();

    OcctQtViewer *occt_viewer=new OcctQtViewer();
    OcctQtControls *occt_controls=new OcctQtControls();

    void set_mousepos();
    void set_backgroundcolor(QColor color);

private slots:
    void on_actionboundary_show_triggered();
    void on_actionboundary_hide_triggered();
    void on_actioncube_hide_triggered();
    void on_actioncube_show_triggered();
    void on_actiontriedron_hide_triggered();
    void on_actiontriedron_show_triggered();
    void on_actionsolid_wireframe_triggered();
    void on_actionsolid_shaded_triggered();
    void on_actionmodel_orthographic_triggered();
    void on_actionmodel_perspective_triggered();
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
    void on_comboBox_currentIndexChanged(int position);

private:
    Ui::OcctQtWidget *ui;
};

#endif // OCCTQTWIDGET_H
