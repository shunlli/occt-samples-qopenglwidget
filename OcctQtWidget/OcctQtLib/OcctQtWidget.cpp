#include "OcctQtWidget.h"
#include "ui_OcctQtWidget.h"

//! Stdlib.
#include <vector>

//! Occtlib.
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRep_Tool.hxx>
#include <examplewriter.h>
#include <Geom_Circle.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Curve.hxx>
#include <BRepAdaptor_Curve.hxx>

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

    //! For the sketcher, set view top and orthograpic.
    occt_viewer->set_orthographic();
    occt_viewer->View()->SetProj(V3d_Zpos);
    occt_viewer->View()->FitAll(0.01,Standard_True);

    //! Connect control stuff.
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

    connect(occt_controls, &OcctQtControls::toolButton_draw_cancel_pressed, this, &OcctQtWidget::on_toolButton_draw_cancel_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_point_pressed, this, &OcctQtWidget::on_toolButton_draw_point_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_2p_line_pressed, this, &OcctQtWidget::on_toolButton_draw_2p_line_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_3p_arc_pressed, this, &OcctQtWidget::on_toolButton_draw_3p_arc_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_3p_cp_arc_pressed, this, &OcctQtWidget::on_toolButton_draw_3p_cp_arc_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_2p_circle_pressed, this, &OcctQtWidget::on_toolButton_draw_2p_circle_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_3p_circle_pressed, this, &OcctQtWidget::on_toolButton_draw_3p_circle_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_2p_tan_circle_pressed, this, &OcctQtWidget::on_toolButton_draw_2p_tan_circle_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_3p_tan_circle_pressed, this, &OcctQtWidget::on_toolButton_draw_3p_tan_circle_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_bspline_pressed, this, &OcctQtWidget::on_toolButton_draw_bspline_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_draw_bezier_pressed, this, &OcctQtWidget::on_toolButton_draw_bezier_pressed);

    connect(occt_controls, &OcctQtControls::toolButton_snap_end_pressed, this, &OcctQtWidget::on_toolButton_snap_end_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_mid_pressed, this, &OcctQtWidget::on_toolButton_snap_mid_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_perpendicular_pressed, this, &OcctQtWidget::on_toolButton_snap_perpendicular_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_center_pressed, this, &OcctQtWidget::on_toolButton_snap_center_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_intersection_pressed, this, &OcctQtWidget::on_toolButton_snap_intersection_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_tangent_pressed, this, &OcctQtWidget::on_toolButton_snap_tangent_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_nearest_pressed, this, &OcctQtWidget::on_toolButton_snap_nearest_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_parallel_pressed, this, &OcctQtWidget::on_toolButton_snap_parallel_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_snap_on_toggled, this, &OcctQtWidget::on_toolButton_snap_on_toggled);

    connect(occt_controls, &OcctQtControls::toolButton_trim_pressed, this, &OcctQtWidget::on_toolButton_trim_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_erase_pressed, this, &OcctQtWidget::on_toolButton_erase_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_sketch_color_pressed, this, &OcctQtWidget::on_toolButton_sketch_color_pressed);

    connect(occt_controls, &OcctQtControls::toolButton_plane_front_pressed, this, &OcctQtWidget::on_toolButton_plane_front_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_plane_right_pressed, this, &OcctQtWidget::on_toolButton_plane_right_pressed);
    connect(occt_controls, &OcctQtControls::toolButton_plane_top_pressed, this, &OcctQtWidget::on_toolButton_plane_top_pressed);

    //! Connect keyboard keypress.
    connect(occt_viewer, &OcctQtViewer::F3, this, &OcctQtWidget::on_F3);
    connect(occt_controls, &OcctQtControls::F3, this, &OcctQtWidget::on_F3);
    connect(occt_viewer, &OcctQtViewer::F8, this, &OcctQtWidget::on_F8);
    connect(occt_controls, &OcctQtControls::F8, this, &OcctQtWidget::on_F8);

    //! Connect menu functions dialog.
    connect(occt_controls, &OcctQtControls::toolButton_open_filecenter_pressed, this, &OcctQtWidget::on_toolButton_open_filecenter_pressed);

    //! Pop up menu
    connect(occt_controls, &OcctQtControls::toolButton_settings_pressed, this, &OcctQtWidget::on_toolButton_settings_pressed);

    //! Connect menu settings dialog.
    connect(occt_menu, &OcctQtMenu::checkBox_orthograpic_pressed, this, &OcctQtWidget::on_checkBox_orthograpic_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_perspective_pressed, this, &OcctQtWidget::on_checkBox_perspective_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_navi_cube_show_pressed, this, &OcctQtWidget::on_checkBox_navi_cube_show_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_navi_cube_hide_pressed, this, &OcctQtWidget::on_checkBox_navi_cube_hide_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_triedron_show_pressed, this, &OcctQtWidget::on_checkBox_triedron_show_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_triedron_hide_pressed, this, &OcctQtWidget::on_checkBox_triedron_hide_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_boundary_show_pressed, this, &OcctQtWidget::on_checkBox_boundary_show_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_boundary_hide_pressed, this, &OcctQtWidget::on_checkBox_boundary_hide_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_shaded_pressed, this, &OcctQtWidget::on_checkBox_shaded_pressed);
    connect(occt_menu, &OcctQtMenu::checkBox_wireframe_pressed, this, &OcctQtWidget::on_checkBox_wireframe_pressed);

    //! Connect filedialog signals.
    connect(occt_file, &OcctQtFile::toolButton_open_document_pressed, this, &OcctQtWidget::on_toolButton_open_document_pressed);
    connect(occt_file, &OcctQtFile::toolButton_save_document_pressed, this, &OcctQtWidget::on_toolButton_save_document_pressed);
    connect(occt_file, &OcctQtFile::toolButton_close_document_pressed, this, &OcctQtWidget::on_toolButton_close_document_pressed);
}

//! Destructor.
OcctQtWidget::~OcctQtWidget()
{
    delete ui;
}

void OcctQtWidget::on_F3(bool checked){
    occt_viewer->mode_snap=checked;
    if(checked){
        occt_controls->tlb_snap->setChecked(1);
    } else {
        occt_controls->tlb_snap->setChecked(0);
    }
}

void OcctQtWidget::on_F8(bool checked){
    occt_viewer->mode_ortho=checked;
    occt_controls->tlb_ortho->setChecked(checked);
    //occt_viewer->mySketcher->SetOrtho(checked);
    if(checked){
        occt_viewer->mySketcher->SetOrtho(Sketcher_OrthoType::OrthoOn);
    } else {
        occt_viewer->mySketcher->SetOrtho(Sketcher_OrthoType::OrthoOff);
    }
}

//! Sketcher plane to draw at. (front,top,right).
void OcctQtWidget::on_toolButton_plane_front_pressed(){
    occt_viewer->mySketcher->SetCoordinateSystem(gp::ZOX());
}

void OcctQtWidget::on_toolButton_plane_right_pressed(){
    occt_viewer->mySketcher->SetCoordinateSystem(gp::YOZ());
}

void OcctQtWidget::on_toolButton_plane_top_pressed(){
    occt_viewer->mySketcher->SetCoordinateSystem(gp::XOY());
}

//! Sketcher draw.
void OcctQtWidget::on_toolButton_draw_cancel_pressed(){
    occt_viewer->mySketcher->OnCancel();
}


//! Sketcher set color.
void OcctQtWidget::on_toolButton_sketch_color_pressed(){

    QColor col;
    QColorDialog *cd = new QColorDialog();
    if(cd->exec()){
        col=cd->selectedColor();
    }

    //! Map colors from 0-255 range to 0-1 range.
    double r=col.red()/255;
    double g=col.green()/255;
    double b=col.blue()/255;
    //! Transparancy level is done in myContext.setTrans...
    double a=col.alpha()/255;

    Quantity_Color c;
    c.SetValues(r,g,b,Quantity_TypeOfColor::Quantity_TOC_sRGB);
    //! Converse rgb to name.
    Quantity_NameOfColor name=c.Name();
    occt_viewer->mySketcher->SetColor(name);
}

void OcctQtWidget::on_toolButton_draw_point_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Point_Method);
}

void OcctQtWidget::on_toolButton_draw_3p_circle_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Circle3P_Method);
}

void OcctQtWidget::on_toolButton_draw_2p_line_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Line2P_Method);
}

void OcctQtWidget::on_toolButton_draw_3p_arc_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Arc3P_Method);
}

void OcctQtWidget::on_toolButton_draw_3p_cp_arc_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::ArcCenter2P_Method);
}

void OcctQtWidget::on_toolButton_draw_2p_circle_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::CircleCenterRadius_Method);
}

void OcctQtWidget::on_toolButton_draw_2p_tan_circle_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Circle2PTan_Method);
}

void OcctQtWidget::on_toolButton_draw_3p_tan_circle_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Circle3Tan_Method);
}

void OcctQtWidget::on_toolButton_draw_bspline_pressed(){
    //occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::BezierCurve_Method);
    std::cout<<"not available yet."<<std::endl;
}

void OcctQtWidget::on_toolButton_draw_bezier_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::BezierCurve_Method);
}

//! Sketcher snap.
void OcctQtWidget::on_toolButton_snap_end_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapEnd);
}

void OcctQtWidget::on_toolButton_snap_mid_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapMiddle);
}

void OcctQtWidget::on_toolButton_snap_center_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapCenter);
}

void OcctQtWidget::on_toolButton_snap_perpendicular_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapPerpendicular);
}

void OcctQtWidget::on_toolButton_snap_intersection_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapIntersection);
}

void OcctQtWidget::on_toolButton_snap_tangent_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapTangent);
}

void OcctQtWidget::on_toolButton_snap_nearest_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapNearest);
}

void OcctQtWidget::on_toolButton_trim_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Trim_Method);
}

void OcctQtWidget::on_toolButton_erase_pressed(){
    occt_viewer->mySketcher->ObjectAction(Sketcher_ObjectTypeOfMethod::Nothing_Method);
    //occt_viewer->mySketcher->DeleteSelectedObject();
}

void OcctQtWidget::on_toolButton_snap_on_toggled(bool checked){
    if(checked){
        occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapAnalyse);
        std::cout<<"snap analyse on"<<std::endl;
    } else {
        occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapNothing);
        std::cout<<"snap analyse off"<<std::endl;
    }
}

void OcctQtWidget::on_toolButton_snap_parallel_pressed(){
    occt_viewer->mySketcher->SetSnap(Sketcher_SnapType::SnapParallel);
}

void OcctQtWidget::on_toolButton_save_document_pressed(QPair<QString,QString> data){

    //! Extenstion of data.second is .dxf
    if(data.second=="Dxf-Files (*.dxf)"){

        std::string filename=data.first.toStdString()+".dxf";
        dxfRW dxf(filename.c_str());
        ExampleWriter writer(dxf);

        for(unsigned int i=0; i<stepfilevec.size(); i++){
            for(unsigned int j=0; j<stepfilevec.at(i).shapevec.size(); j++){

                TopExp_Explorer explorer;

                //! Get the shape from a ais_shape.
                Handle(AIS_Shape) anAISObj = Handle(AIS_Shape)::DownCast(stepfilevec.at(i).shapevec.at(j));

                for(explorer.Init(anAISObj->Shape(), TopAbs_EDGE); explorer.More(); explorer.Next()){

                    const TopoDS_Edge& edge = TopoDS::Edge(explorer.Current());

                    TopoDS_Vertex v0,v1;
                    TopExp::Vertices(edge,v0,v1);
                    gp_Pnt p0= BRep_Tool::Pnt(v0);
                    gp_Pnt p1= BRep_Tool::Pnt(v1);

                    std::cout<<"edge p1 x: "<<p0.X()<<" y:"<<p0.Y()<<" z:"<<p0.Z()<<std::endl;
                    std::cout<<"edge p2 x: "<<p1.X()<<" y:"<<p1.Y()<<" z:"<<p1.Z()<<std::endl;

                    //! Start angle = U1, End angle = U2.
                    Standard_Real R,U1,U2;
                    Handle (Geom_Curve) C1 = BRep_Tool::Curve(TopoDS::Edge(explorer.Current()), U1, U2);
                    std::cout<<"U1:"<<U1<<std::endl;
                    std::cout<<"U2:"<<U2<<std::endl;
                    Handle (Geom_Circle) C2 = Handle (Geom_Circle)::DownCast(C1);

                    //! Find arc start + end points. Another example:
                    /*
                    BRepAdaptor_Curve curve(edge);
                    double fp = curve.FirstParameter(); std::cout<<"fp:"<<fp<<std::endl;
                    double lp = curve.LastParameter();  std::cout<<"lp:"<<lp<<std::endl;
                    gp_Pnt parc1, parc2;
                    curve.D0(fp, parc1); //! Outputs Point parc1.
                    curve.D0(lp, parc2);
                    std::cout<<"arc start x:"<<parc1.X()<<" y:"<<parc1.Y()<<" z:"<<parc1.Z()<<std::endl;
                    std::cout<<"arc end   x:"<<parc2.X()<<" y:"<<parc2.Y()<<" z:"<<parc2.Z()<<std::endl;*/

                    //! It has arc or circle values.
                    if(!C2.IsNull()){
                        /*
                        //! Check if arc is closed with tollerance.
                        if(parc1.IsEqual(parc2,1)){
                            std::cout<<"closed arc found, radius :"<<C2->Radius()<<std::endl;
                            //! Full closed circle.
                            DRW_Circle circle;
                            //! Circle center.
                            circle.basePoint.x = C2.get()->Location().X();
                            circle.basePoint.y = C2.get()->Location().Y();
                            circle.basePoint.z = C2.get()->Location().Z();
                            circle.radious=C2->Radius();
                            writer.circlevec.push_back(circle);
                        } else {*/
                        //! Its a arc, not a circle..

                        DRW_Arc arc;
                        //! Arc center.
                        arc.basePoint.x = C2.get()->Location().X();
                        arc.basePoint.y = C2.get()->Location().Y();
                        arc.basePoint.z = C2.get()->Location().Z();
                        arc.radious=C2->Radius();

                        //! It looks like the start and end angle has to be swapped.
                        //! The U1 & U2 values of opencascade does't seem to match aucocad angle values. So we calculate them ourselve's.
                        double start = atan2(p0.Y()-C2.get()->Location().Y(), p0.X() - C2.get()->Location().X());
                        double end =  atan2(p1.Y()-C2.get()->Location().Y(), p1.X() - C2.get()->Location().X());
                        //! Autocad solver.
                        if(end<start){
                            end+=2*M_PI;
                        }

                        arc.staangle=end;
                        arc.endangle=start;

                        writer.arcvec.push_back(arc);
                    }

                    //! It is not an arc or circe.
                    if(C2.IsNull()){
                        DRW_Line line;
                        line.basePoint.x = p0.X();
                        line.basePoint.y = p0.Y();
                        line.basePoint.z = p0.Z();
                        line.secPoint.x = p1.X();
                        line.secPoint.y = p1.Y();
                        line.secPoint.z = p1.Z();
                        writer.linevec.push_back(line);
                    }
                }
            }
        }
        //! Write the dxf file.
        //! Here it will write all data at once to the dxf file.
        dxf.write(&writer, DRW::Version::AC1027, false);

        //! Clean up.
        writer.linevec.clear();
        writer.arcvec.clear();
        writer.circlevec.clear();
        writer.pointvec.clear();
    }
}

void OcctQtWidget::on_toolButton_open_document_pressed(QPair<QString,QString> data){
    //! Get the shapevec from the filereader. Put it in a struct.

    //! Is it a stepfile?
    if(data.second=="Step-Files (*.step)"){
        stepfilevec.push_back({data.first,occt_functions->load_stepfile(data.first)});
        //! Pass the struct to the display.
        occt_viewer->show_shapevec(stepfilevec.back().shapevec);
    }

    if(data.second=="Ngc-Files (*.ngc)"){
        stepfilevec.push_back({data.first,occt_functions->load_ngcfile(data.first)});
        occt_viewer->show_shapevec(stepfilevec.back().shapevec);
    }

    if(data.second=="Dxf-Files (*.dxf)"){
        stepfilevec.push_back({data.first,occt_functions->load_dxffile(data.first)});
        occt_viewer->show_shapevec(stepfilevec.back().shapevec);
    }

    if(data.second=="Stl-Files (*.stl)"){
        stepfilevec.push_back({data.first,occt_functions->load_stlfile(data.first)});
        occt_viewer->show_shapevec(stepfilevec.back().shapevec);
    }
    occt_viewer->redraw();
}

void OcctQtWidget::on_toolButton_close_document_pressed(QString str){

    std::vector<STEPFILE>::iterator it0,it1;
    std::vector<Handle(AIS_Shape)>::iterator it2;

    for(it1=stepfilevec.begin(); it1!=stepfilevec.end(); it1++){
        if(it1->filename==str){
            break;
        }
    }

    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it2=it1->shapevec.begin(); it2!=it1->shapevec.end(); it2++){
            occt_viewer->remove_shape(*it2);
        }
    }
    stepfilevec.erase(it1);
    occt_viewer->redraw();
}

void OcctQtWidget::on_toolButton_open_filecenter_pressed(){
    occt_file->show();
}

void OcctQtWidget::on_checkBox_shaded_pressed(){
    std::vector<STEPFILE>::iterator it0;
    std::vector<Handle(AIS_Shape)>::iterator it1;
    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it1=it0->shapevec.begin(); it1!=it0->shapevec.end(); it1++){
            occt_viewer->show_as_shaded(*it1);
        }
    }
}

void OcctQtWidget::on_checkBox_wireframe_pressed(){
    std::vector<STEPFILE>::iterator it0;
    std::vector<Handle(AIS_Shape)>::iterator it1;
    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it1=it0->shapevec.begin(); it1!=it0->shapevec.end(); it1++){
            occt_viewer->show_as_wireframe(*it1);
        }
    }
}

void OcctQtWidget::on_checkBox_boundary_show_pressed(){
    std::vector<STEPFILE>::iterator it0;
    std::vector<Handle(AIS_Shape)>::iterator it1;
    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it1=it0->shapevec.begin(); it1!=it0->shapevec.end(); it1++){
            occt_viewer->show_boundary(*it1);
        }
    }
}

void OcctQtWidget::on_checkBox_boundary_hide_pressed(){
    std::vector<STEPFILE>::iterator it0;
    std::vector<Handle(AIS_Shape)>::iterator it1;
    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it1=it0->shapevec.begin(); it1!=it0->shapevec.end(); it1++){
            occt_viewer->hide_boundary(*it1);
        }
    }
}

void OcctQtWidget::on_checkBox_triedron_show_pressed(){
    occt_viewer->show_triedron();
}

void OcctQtWidget::on_checkBox_triedron_hide_pressed(){
    occt_viewer->hide_triedron();
}

void OcctQtWidget::on_checkBox_navi_cube_show_pressed(){
    occt_viewer->show_cube();
}

void OcctQtWidget::on_checkBox_navi_cube_hide_pressed(){
    occt_viewer->hide_cube();
}

void OcctQtWidget::on_checkBox_orthograpic_pressed(){
    occt_viewer->set_orthographic();
}

void OcctQtWidget::on_checkBox_perspective_pressed(){
    occt_viewer->set_perspective();
}

//! Menu settings.
void OcctQtWidget::on_toolButton_settings_pressed(){
    occt_menu->show();
}

//! Background color given by the user's "pallete" color input.
void OcctQtWidget::set_backgroundcolor(QColor color){
    occt_viewer->set_backgroundcolor(color.red(),color.green(),color.blue());
}

//! Update xyz mouseposition labels. The labels updated by mouse hovering a active shape.
void OcctQtWidget::set_mousepos(){
    occt_controls->update_labels(occt_viewer->mousepos);
}

//! Function calls.
void OcctQtWidget::on_verticalSlider_sliderMoved(int position)
{
    double value=0.01*double(position);
    std::vector<STEPFILE>::iterator it0;
    std::vector<Handle(AIS_Shape)>::iterator it1;
    for(it0=stepfilevec.begin(); it0!=stepfilevec.end(); it0++){
        for(it1=it0->shapevec.begin(); it1!=it0->shapevec.end(); it1++){
            occt_viewer->set_tranceparancy(*it1,value);
        }
    }
    occt_viewer->View()->Redraw();
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

std::vector<Handle(AIS_Shape)> OcctQtWidget::load_stepfile(QString filename){
    std::vector<Handle(AIS_Shape)> shapevec = occt_functions->load_stepfile(filename);
    return shapevec;
}

