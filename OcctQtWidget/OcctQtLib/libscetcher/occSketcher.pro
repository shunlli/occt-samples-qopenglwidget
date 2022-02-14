#-------------------------------------------------
#
# Project created by QtCreator 2013-08-18T15:52:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = occSketcher
TEMPLATE = app

SOURCES += Main.cxx     \
    Geom2d_Arc.cxx \
    Geom2d_Edge.cxx \
    Sketcher.cxx \
    Sketcher_AnalyserSnap.cxx \
    Sketcher_Command.cxx \
    Sketcher_CommandArc3P.cxx \
    Sketcher_CommandArcCenter2P.cxx \
    Sketcher_CommandBezierCurve.cxx \
    Sketcher_CommandCircle2PTan.cxx \
    Sketcher_CommandCircle3P.cxx \
    Sketcher_CommandCircle3Tan.cxx \
    Sketcher_CommandCircleCenterRadius.cxx \
    Sketcher_CommandCircleP2Tan.cxx \
    Sketcher_CommandLine2P.cxx \
    Sketcher_CommandPoint.cxx \
    Sketcher_CommandTrim.cxx \
    Sketcher_GUI.cxx \
    Sketcher_Object.cxx \
    Sketcher_Property.cxx \
    Sketcher_PropertyArc.cxx \
    Sketcher_PropertyCircle.cxx \
    Sketcher_PropertyLine.cxx \
    Sketcher_PropertyPoint.cxx \
    Sketcher_QtGUI.cxx \
    Sketcher_Snap.cxx \
    Sketcher_SnapCenter.cxx \
    Sketcher_SnapEnd.cxx \
    Sketcher_SnapIntersection.cxx \
    Sketcher_SnapLine.cxx \
    Sketcher_SnapLineParallel.cxx \
    Sketcher_SnapLinePerpendicular.cxx \
    Sketcher_SnapMiddle.cxx \
    Sketcher_SnapNearest.cxx \
    Sketcher_SnapTangent.cxx \
    occQt.cpp \
    occView.cpp

CONFIG += c++11

HEADERS  += Sketcher.h   \
    Geom2d_Arc.hxx \
    Geom2d_Edge.hxx \
    Sketcher.hxx \
    Sketcher_AnalyserSnap.hxx \
    Sketcher_Command.hxx \
    Sketcher_CommandArc3P.hxx \
    Sketcher_CommandArcCenter2P.hxx \
    Sketcher_CommandBezierCurve.hxx \
    Sketcher_CommandCircle2PTan.hxx \
    Sketcher_CommandCircle3P.hxx \
    Sketcher_CommandCircle3Tan.hxx \
    Sketcher_CommandCircleCenterRadius.hxx \
    Sketcher_CommandCircleP2Tan.hxx \
    Sketcher_CommandLine2P.hxx \
    Sketcher_CommandPoint.hxx \
    Sketcher_CommandTrim.hxx \
    Sketcher_GUI.hxx \
    Sketcher_Object.hxx \
    Sketcher_ObjectGeometryType.hxx \
    Sketcher_ObjectType.hxx \
    Sketcher_ObjectTypeOfMethod.hxx \
    Sketcher_Property.hxx \
    Sketcher_PropertyArc.hxx \
    Sketcher_PropertyCircle.hxx \
    Sketcher_PropertyLine.hxx \
    Sketcher_PropertyPoint.hxx \
    Sketcher_QtGUI.hxx \
    Sketcher_Snap.hxx \
    Sketcher_SnapCenter.hxx \
    Sketcher_SnapEnd.hxx \
    Sketcher_SnapIntersection.hxx \
    Sketcher_SnapLine.hxx \
    Sketcher_SnapLineParallel.hxx \
    Sketcher_SnapLinePerpendicular.hxx \
    Sketcher_SnapMiddle.hxx \
    Sketcher_SnapNearest.hxx \
    Sketcher_SnapTangent.hxx \
    Sketcher_SnapType.hxx \
    occQt.h \
    occView.h
    

RESOURCES += \
    occSketcher.qrc \
    occSketcher.qrc

# Opencascade
INCLUDEPATH += /opt/opencascade/oce-upstream-V7_5_0beta/inc \
               /opt/opencascade/oce-upstream-V7_5_0beta/src
LIBS+= -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/lib \
       -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/libd

LIBS += -lTKGeomAlgo -lTKMesh -lTKHLR -lTKBO -lTKShHealing
LIBS += -lTKPrim
LIBS += -lTKernel -lTKMath -lTKTopAlgo -lTKService
LIBS += -lTKG2d -lTKG3d -lTKV3d -lTKOpenGl
LIBS += -lTKBRep -lTKXSBase -lTKGeomBase
LIBS += -lTKXSDRAW
LIBS += -lTKLCAF -lTKXCAF -lTKCAF -lTKVCAF
LIBS += -lTKCDF -lTKBin -lTKBinL -lTKBinXCAF -lTKXml -lTKXmlL -lTKXmlXCAF
# -- IGES support
LIBS += -lTKIGES
# -- STEP support
LIBS += -lTKSTEP -lTKXDESTEP -lTKXDEIGES -lTKSTEPAttr -lTKSTEPBase -lTKSTEP209
# -- STL support
LIBS += -lTKSTL
# -- OBJ/glTF support
LIBS += -lTKRWMesh -lTKMeshVS
# -- VRML support
LIBS += -lTKVRML
# -- ViewerTest
LIBS += -lTKViewerTest

LIBS +=         \
    -lTKernel   \
    -lTKMath    \
    -lTKG3d     \
    -lTKBRep    \
    -lTKGeomBase\
    -lTKGeomAlgo\
    -lTKTopAlgo \
    -lTKPrim    \
    -lTKBO      \
    -lTKBool    \
    -lTKOffset  \
    -lTKService \
    -lTKV3d     \
    -lTKOpenGl  \
    -lTKFillet

FORMS += \
    occQt.ui

DISTFILES += \
    res/SampleImportExport.png \
    res/cascade.png \
    res/close.png \
    res/cursor_rotate.png \
    res/cursor_zoom.png \
    res/delete.png \
    res/document.png \
    res/erase.PNG \
    res/grid.PNG \
    res/help.png \
    res/icon.qm \
    res/inputArc.png \
    res/inputArc3p.PNG \
    res/inputArcCenter2p.PNG \
    res/inputBezierCurve.PNG \
    res/inputBsplineCurve.PNG \
    res/inputCircle.png \
    res/inputCircle2.PNG \
    res/inputCircle2PTan.PNG \
    res/inputCircle3p.PNG \
    res/inputCircle3tan.PNG \
    res/inputCircleP2Tan.png \
    res/inputLine.png \
    res/inputPoint.PNG \
    res/lamp.png \
    res/new.png \
    res/plane.PNG \
    res/property.PNG \
    res/redraw.png \
    res/snapanalyser.PNG \
    res/snapcenter.PNG \
    res/snapend.PNG \
    res/snapintersection.PNG \
    res/snapmiddle.PNG \
    res/snapnearest.PNG \
    res/snapnon.PNG \
    res/snapparallel.PNG \
    res/snapperpendicular.PNG \
    res/snaptangent.PNG \
    res/string.qm \
    res/tile.png \
    res/tool_color.png \
    res/tool_delete.png \
    res/tool_material.png \
    res/tool_shading.png \
    res/tool_transparency.png \
    res/tool_wireframe.png \
    res/trimcurve.PNG \
    res/view_axo.png \
    res/view_back.png \
    res/view_bottom.png \
    res/view_comp_off.png \
    res/view_comp_on.png \
    res/view_fitall.png \
    res/view_fitarea.png \
    res/view_front.png \
    res/view_glpan.png \
    res/view_left.png \
    res/view_pan.png \
    res/view_reset.png \
    res/view_right.png \
    res/view_rotate.png \
    res/view_top.png \
    res/view_zoom.png
