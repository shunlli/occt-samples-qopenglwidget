#include "OcctQtFunctions.h"

#include <OSD.hxx>
#include <AIS_Trihedron.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Selection.hxx>
#include <AIS_ColoredShape.hxx>
#include <AIS_ColoredDrawer.hxx>
#include <BRepLib.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepTools_ReShape.hxx>
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <gp_Trsf.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <STEPCAFControl_Controller.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_CartesianPoint.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeEllipse.hxx>
#include <GC_MakeSegment.hxx>
#include <gce_MakeRotation.hxx>
#include <TopExp.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <TDF_Label.hxx>
#include <TDF_AttributeIterator.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_UAttribute.hxx>
#include <TNaming_NamedShape.hxx>
#include <TopTools.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include "Geom_Axis2Placement.hxx"
#include <GCE2d_MakeSegment.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <XCAFDoc_Area.hxx>
#include <XCAFDoc_Centroid.hxx>
#include <XCAFDoc_Datum.hxx>
#include <XCAFDoc_Dimension.hxx>
#include <XCAFDoc_Location.hxx>
#include <XCAFDoc_Volume.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <Quantity_Color.hxx>
#include <Quantity_ColorRGBA.hxx>

#include "XCAFPrs_DocumentExplorer.hxx"
#include <TDataStd_Name.hxx>
#include <XCAFDoc_AssemblyItemId.hxx>
#include <XCAFDoc_AssemblyItemRef.hxx>

#include <BRepTools.hxx>
#include <Font_BRepFont.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <Bnd_Box.hxx>

#include "gp_Elips.hxx"
#include <NCollection_Mat4.hxx>
#include <gp_Quaternion.hxx>

#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPoints.hxx>
#include <AIS_PointCloud.hxx>
#include <Graphic3d_NameOfMaterial.hxx>

// libgcode
#include <libgcode/gcode_parser.h>

// libocct
#include <libocct/draw_primitives.h>

OcctQtFunctions::OcctQtFunctions()
{

}

std::vector<Handle(AIS_Shape)> OcctQtFunctions::load_stepfile(QString filename)
{
    //! Empty temponairy bucket, the visit function will fill up the bucket for one stepfile.
    Ais_ShapeVec.clear();

    STEPCAFControl_Controller::Init();

    Handle(TDocStd_Document) aDoc;
    Handle(XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
    anApp->NewDocument("MDTV-XCAF", aDoc);

    STEPCAFControl_Reader aStepReader;
    aStepReader.SetColorMode(true);
    aStepReader.SetNameMode(true);
    aStepReader.SetLayerMode(true);
    aStepReader.SetPropsMode(true);

    aStepReader.ReadFile (filename.toStdString().c_str());
    aStepReader.Transfer (aDoc);

    TDF_Label aRootLabel = aDoc->Main();

    aShapeTool = XCAFDoc_DocumentTool::ShapeTool(aRootLabel);
    aColorTool = XCAFDoc_DocumentTool::ColorTool(aRootLabel);

    Visit(aRootLabel);

    return Ais_ShapeVec;
}

void OcctQtFunctions::Visit(const TDF_Label& theLabel)
{
    //! theLabel.EntryDump(std::cout);
    Quantity_Color aColor;
    TopoDS_Shape aShape;
    Handle(TDataStd_Name) aName;
    if (theLabel.FindAttribute(TDataStd_Name::GetID(), aName)){
        //! std::cout << "  Name: " << aName->Get() << std::endl;
    }
    bool skip=0;
    if (aShapeTool->IsShape(theLabel))
    {
        //! if a shape can be made from the current label, look for the color of that label:
        if(aShapeTool->GetShape(theLabel, aShape)){
            if(aColorTool->GetColor(aShape,XCAFDoc_ColorSurf,aColor)){
                skip=0;
            } else { skip=1;}
        }
        if(skip==0){
            Ais_ShapeVec.push_back(new AIS_Shape(aShape));
            Ais_ShapeVec.back()->SetColor(aColor);
            Ais_ShapeVec.back()->SetDisplayMode(AIS_Shaded);
            Ais_ShapeVec.back()->Attributes()->SetFaceBoundaryDraw(true);
            Ais_ShapeVec.back()->Attributes()->SetFaceBoundaryAspect(
                        new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.));
            Ais_ShapeVec.back()->Attributes()->SetIsoOnTriangulation(true);
            //! Temporairy stepfile preview:
            //! m_context->Display(Ais_ShapeVec.back(),Standard_False);
        }
    }
    /*! Repeat the visit function for each childmember. */
    for (TDF_ChildIterator c(theLabel); c.More(); c.Next())
    {
        Visit(c.Value());
    }
}

std::vector<Handle(AIS_Shape)> OcctQtFunctions::load_dxffile(QString filename){
    Ais_ShapeVec.clear();
    Ais_ShapeVec=libdxfrw_functions().open_dxf_file(filename.toStdString());
    return Ais_ShapeVec;
}

std::vector<Handle(AIS_Shape)> OcctQtFunctions::load_ngcfile(QString filename){
    Ais_ShapeVec.clear();

    gcode_parser::GCODE gc=gcode_parser().process_gcode(filename.toStdString());

    gp_Pnt p1,p2,pc;

    //! process to cad data
    for(unsigned int i=0; i<gc.blockvec.size(); i++){

        p2={gc.blockvec.at(i).X,gc.blockvec.at(i).Y,gc.blockvec.at(i).Z};
        double I=gc.blockvec.at(i).I;
        double J=gc.blockvec.at(i).J;

        //! Mention K is now Z.
        double Z=gc.blockvec.at(i).Z;
        pc.SetX(p1.X()+I);
        pc.SetY(p1.Y()+J);
        pc.SetZ(p1.Z()+Z);

        if(i>0 && gc.blockvec.at(i).G==0){
            Ais_ShapeVec.push_back(draw_primitives().draw_3d_line(p1,p2));
            Ais_ShapeVec.back()=draw_primitives().colorize(Ais_ShapeVec.back(),Quantity_NOC_BLUE,0);
        }
        if(i>0 && gc.blockvec.at(i).G==1){
            Ais_ShapeVec.push_back(draw_primitives().draw_3d_line(p1,p2));
            Ais_ShapeVec.back()=draw_primitives().colorize(Ais_ShapeVec.back(),Quantity_NOC_BLACK,0);
        }
        if(i>0 && (gc.blockvec.at(i).G==2)){

            //! Arc section
            //! X=xend, Y=yend. For arc given a G0 startposition and a XY endposition. http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g2-g3
            //! I=offset xcenter-xstart, J=offset ycenter-ystart, G2=clockwise (cw), G3=counterclockwise (ccw)
            Ais_ShapeVec.push_back(draw_primitives().draw_cp_3d_arc(p2,p1,pc));
            Ais_ShapeVec.back()=draw_primitives().colorize(Ais_ShapeVec.back(),Quantity_NOC_BLACK,0);
        }
        if(i>0 && (gc.blockvec.at(i).G==3)){
            Ais_ShapeVec.push_back(draw_primitives().draw_cp_3d_arc(p1,p2,pc));
            Ais_ShapeVec.back()=draw_primitives().colorize(Ais_ShapeVec.back(),Quantity_NOC_BLACK,0);
        }
        p1=p2;
    }
    return Ais_ShapeVec;
}

std::vector<Handle(AIS_Shape)> OcctQtFunctions::load_stlfile(QString filename){

}




