#include "OcctQtMenu.h"
#include "ui_OcctQtMenu.h"

OcctQtMenu::OcctQtMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcctQtMenu)
{
    ui->setupUi(this);
}

OcctQtMenu::~OcctQtMenu()
{
    delete ui;
}

void OcctQtMenu::on_checkBox_perspective_pressed()
{
    ui->checkBox_orthograpic->setChecked(false);
    checkBox_perspective_pressed();
}

void OcctQtMenu::on_checkBox_orthograpic_pressed()
{
    ui->checkBox_perspective->setChecked(false);
    checkBox_orthograpic_pressed();
}

void OcctQtMenu::on_checkBox_shaded_pressed()
{
    ui->checkBox_wireframe->setChecked(false);
    checkBox_shaded_pressed();
}

void OcctQtMenu::on_checkBox_navi_cube_show_pressed()
{
    ui->checkBox_navi_cube_hide->setChecked(false);
    checkBox_navi_cube_show_pressed();
}
void OcctQtMenu::on_checkBox_wireframe_pressed()
{
    ui->checkBox_shaded->setChecked(false);
    checkBox_wireframe_pressed();
}

void OcctQtMenu::on_checkBox_triedron_show_pressed()
{
    ui->checkBox_triedron_hide->setChecked(false);
    checkBox_triedron_show_pressed();
}

void OcctQtMenu::on_checkBox_triedron_hide_pressed()
{
    ui->checkBox_triedron_show->setChecked(false);
    checkBox_triedron_hide_pressed();
}

void OcctQtMenu::on_checkBox_boundary_show_pressed()
{
    ui->checkBox_boundary_hide->setChecked(false);
    checkBox_boundary_show_pressed();
}

void OcctQtMenu::on_checkBox_boundary_hide_pressed()
{
    ui->checkBox_boundary_show->setChecked(false);
    checkBox_boundary_hide_pressed();
}

void OcctQtMenu::on_checkBox_navi_cube_hide_pressed()
{
    ui->checkBox_navi_cube_show->setChecked(false);
    checkBox_navi_cube_hide_pressed();
}

void OcctQtMenu::on_buttonBox_accepted()
{
    this->close();
}
