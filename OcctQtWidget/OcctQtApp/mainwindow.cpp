#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OcctQtWidget *occt = new OcctQtWidget(this);
    const QColor color=ui->centralwidget->palette().color(QPalette::ColorRole::Window);
    occt->set_backgroundcolor(color);
    occt->setPalette(ui->centralwidget->palette());
    ui->gridLayout->addWidget(occt);

}

MainWindow::~MainWindow()
{
    delete ui;
}

