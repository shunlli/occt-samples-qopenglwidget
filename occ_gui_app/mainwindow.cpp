#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *layout=new QGridLayout(occt_viewer);
    layout->addWidget(occt_controls,0,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(occt_viewer);

    const QColor color= ui->centralwidget->palette().color(QPalette::ColorRole::Window);
    occt_viewer->set_backgroundcolor(color.red(),color.green(),color.blue());

    connect(timer, &QTimer::timeout, this, &MainWindow::mainloop);
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionwireframe_triggered()
{
    occt_viewer->show_as_wireframe();
}

void MainWindow::on_actionshaded_triggered()
{
    occt_viewer->show_as_shaded();
}

void MainWindow::on_actionboundary_show_triggered()
{
    occt_viewer->show_boundary();
}

void MainWindow::on_actionboundary_hide_triggered()
{
    occt_viewer->hide_boundary();
}

void MainWindow::on_actionorthographic_triggered()
{
    occt_viewer->View()->Camera()->SetProjectionType (Graphic3d_Camera::Projection_Orthographic);
    occt_viewer->View()->Redraw();
    occt_viewer->update();
}

void MainWindow::on_actionperspective_triggered()
{
    occt_viewer->View()->Camera()->SetProjectionType (Graphic3d_Camera::Projection_Perspective);
    occt_viewer->View()->Redraw();
    occt_viewer->update();
}

void MainWindow::on_actioncube_hide_triggered()
{
    occt_viewer->hide_cube();
}

void MainWindow::on_actioncube_show_triggered()
{
    occt_viewer->show_cube();
}

void MainWindow::mainloop(){

    if(!occt_viewer->View().IsNull()){

        occt_controls->lbl_x->setText(QString::number(occt_viewer->aMousePnt.X(),'f',3));
        occt_controls->lbl_y->setText(QString::number(occt_viewer->aMousePnt.Y(),'f',3));
        occt_controls->lbl_z->setText(QString::number(occt_viewer->aMousePnt.X(),'f',3));

        if(occt_controls->btn_zoom_extends->isDown()==true){
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_plus->isDown()==true){
            occt_viewer->UpdateZoom(1);
            occt_viewer->update();
        }
        if(occt_controls->btn_zoom_min->isDown()==true){
            occt_viewer->UpdateZoom(-1);
            occt_viewer->update();
        }
        if(occt_controls->btn_zoom_front->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Yneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_back->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Ypos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_left->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Xneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_right->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Xpos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_top->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Zpos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_bottom->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Zneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_3d->isDown()==true){
            occt_viewer->View()->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->sl_tranceparancy->isSliderDown()){
            double value=0.01*double(occt_controls->sl_tranceparancy->value());
            occt_viewer->set_tranceparancy(value);
            occt_viewer->View()->Redraw();
        }


        if(!oneshot){
            occt_viewer->View()->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
            double value=0.01*double(occt_controls->sl_tranceparancy->value());
            occt_viewer->set_tranceparancy(value);
            occt_viewer->View()->FitAll(0.01,Standard_True);
            occt_viewer->View()->Redraw();
            oneshot=1;
        }

    }





    /// View as wireframe or shaded
    //m_context->SetDisplayMode(AIS_WireFrame, Standard_False);
    // m_context->SetDisplayMode(AIS_Shaded, Standard_False);

}













