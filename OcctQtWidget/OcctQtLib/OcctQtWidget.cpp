#include "OcctQtWidget.h"
#include "ui_OcctQtWidget.h"

//! Creator         : Skynet Cyberdyne.
//! Date            : 01-2021.
//! Location        : Planet Earth.

OcctQtWidget::OcctQtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcctQtWidget)
{
    ui->setupUi(this);

    //! Add the occt_viewer widget.
    QGridLayout *layout=new QGridLayout(occt_viewer);
    //! Add the occt_control widget.
    layout->addWidget(occt_controls,0,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(occt_viewer);

    //! Connect stuff.
    connect(occt_viewer, &OcctQtViewer::mouse_signal, this, &OcctQtWidget::set_mousepos);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_3d_pressed, this, &OcctQtWidget::on_toolButton_zoom_3d_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_back_pressed, this, &OcctQtWidget::on_toolButton_zoom_back_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_front_pressed, this, &OcctQtWidget::on_toolButton_zoom_front_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_left_pressed, this, &OcctQtWidget::on_toolButton_zoom_left_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_right_pressed, this, &OcctQtWidget::on_toolButton_zoom_right_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_top_pressed, this, &OcctQtWidget::on_toolButton_zoom_top_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_bottom_pressed, this, &OcctQtWidget::on_toolButton_zoom_bottom_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_plus_pressed, this, &OcctQtWidget::on_toolButton_zoom_plus_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_min_pressed, this, &OcctQtWidget::on_toolButton_zoom_min_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_zoom_extends_pressed, this, &OcctQtWidget::on_toolButton_zoom_extends_pressed);
    connect(occt_controls, &OcctQtControls::verticalSlider_sliderMoved, this, &OcctQtWidget::on_verticalSlider_sliderMoved);
    connect(occt_controls, &OcctQtControls::comboBox_currentIndexChanged, this, &OcctQtWidget::on_comboBox_currentIndexChanged);
}

//! Destructor.
OcctQtWidget::~OcctQtWidget()
{
    delete ui;
}

//! Background color given by the user's "pallete" color input.
void OcctQtWidget::set_backgroundcolor(QColor color){
    occt_viewer->set_backgroundcolor(color.red(),color.green(),color.blue());
}

//! Update xyz mouseposition labels. The labels updated by mouse hovering a active shape.
void OcctQtWidget::set_mousepos(){
    std::cout<<"mousepos"<<std::endl;
    occt_controls->update_labels(occt_viewer->mousepos);
}

//! Select a mode.
void OcctQtWidget::on_comboBox_currentIndexChanged(int position)
{
    switch (position) {
    case 0:
        occt_viewer->set_perspective();
        break;
    case 1:
        occt_viewer->set_orthographic();
        break;
    case 2:
        occt_viewer->show_as_wireframe();
        break;
    case 3:
        occt_viewer->show_as_shaded();
        break;
    case 4:
        occt_viewer->show_triedron();
        break;
    case 5:
        occt_viewer->hide_triedron();
        break;
    case 6:
        occt_viewer->show_boundary();
        break;
    case 7:
        occt_viewer->hide_boundary();
        break;
    case 8:
        occt_viewer->show_cube();
        break;
    case 9:
        occt_viewer->hide_cube();
        break;
    default:
        //! Rabbit hole. Lost pointer.
        break;
    }
}

//! Function calls.
void OcctQtWidget::on_verticalSlider_sliderMoved(int position)
{
    double value=0.01*double(position);
    occt_viewer->set_tranceparancy(value);
    occt_viewer->View()->Redraw();
}

void OcctQtWidget::on_actionboundary_show_triggered()
{
    occt_viewer->show_boundary();
}

void OcctQtWidget::on_actionboundary_hide_triggered()
{
    occt_viewer->hide_boundary();
}

void OcctQtWidget::on_actioncube_hide_triggered()
{
    occt_viewer->hide_cube();
}

void OcctQtWidget::on_actioncube_show_triggered()
{
    occt_viewer->show_cube();
}

void OcctQtWidget::on_actiontriedron_hide_triggered()
{
    occt_viewer->hide_triedron();
}

void OcctQtWidget::on_actiontriedron_show_triggered()
{
    occt_viewer->show_triedron();
}

void OcctQtWidget::on_actionsolid_wireframe_triggered()
{
    occt_viewer->show_as_wireframe();
}

void OcctQtWidget::on_actionsolid_shaded_triggered()
{
    occt_viewer->show_as_shaded();
}

void OcctQtWidget::on_actionmodel_orthographic_triggered()
{
    occt_viewer->set_orthographic();
}

void OcctQtWidget::on_actionmodel_perspective_triggered()
{
    occt_viewer->set_perspective();
}

void OcctQtWidget::on_toolButton_zoom_3d_pressed()
{
    occt_viewer->View()->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_back_pressed()
{
    occt_viewer->View()->SetProj(V3d_Ypos);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_bottom_pressed()
{
    occt_viewer->View()->SetProj(V3d_Zneg);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_front_pressed()
{
    occt_viewer->View()->SetProj(V3d_Yneg);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_left_pressed()
{
    occt_viewer->View()->SetProj(V3d_Xneg);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_right_pressed()
{
    occt_viewer->View()->SetProj(V3d_Xpos);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_top_pressed()
{
    occt_viewer->View()->SetProj(V3d_Zpos);
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_extends_pressed()
{
    occt_viewer->View()->FitAll(0.01,Standard_True);
}

void OcctQtWidget::on_toolButton_zoom_plus_pressed()
{
    occt_viewer->UpdateZoom(1);
    occt_viewer->update();
}

void OcctQtWidget::on_toolButton_zoom_min_pressed()
{
    occt_viewer->UpdateZoom(-1);
    occt_viewer->update();
}
