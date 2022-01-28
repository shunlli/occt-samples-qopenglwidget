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
    void comboBox_currentIndexChanged(int index);

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
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::OcctQtControls *ui;
};

#endif // OCCTQTCONTROLS_H
