#ifndef OCCTQTMENU_H
#define OCCTQTMENU_H

#include <QWidget>
#include <QAbstractButton>
#include <iostream>

namespace Ui {
class OcctQtMenu;
}

class OcctQtMenu : public QWidget
{
    Q_OBJECT

public:
    explicit OcctQtMenu(QWidget *parent = nullptr);
    ~OcctQtMenu();

signals:
    void checkBox_perspective_pressed();
    void checkBox_orthograpic_pressed();
    void checkBox_navi_cube_show_pressed();
    void checkBox_shaded_pressed();
    void checkBox_wireframe_pressed();
    void checkBox_triedron_show_pressed();
    void checkBox_triedron_hide_pressed();
    void checkBox_boundary_show_pressed();
    void checkBox_boundary_hide_pressed();
    void checkBox_navi_cube_hide_pressed();

private slots:
    void on_checkBox_perspective_pressed();
    void on_checkBox_orthograpic_pressed();
    void on_checkBox_navi_cube_show_pressed();
    void on_checkBox_shaded_pressed();
    void on_checkBox_wireframe_pressed();
    void on_checkBox_triedron_show_pressed();
    void on_checkBox_triedron_hide_pressed();
    void on_checkBox_boundary_show_pressed();
    void on_checkBox_boundary_hide_pressed();
    void on_checkBox_navi_cube_hide_pressed();

    void on_buttonBox_accepted();

private:
    Ui::OcctQtMenu *ui;
};

#endif // OCCTQTMENU_H
