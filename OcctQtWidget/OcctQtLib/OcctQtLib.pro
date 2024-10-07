QT += widgets gui

TEMPLATE = lib
DEFINES += OCCTQT_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OcctQtControls.cpp \
    OcctQtFile.cpp \
    OcctQtFunctions.cpp \
    OcctQtMenu.cpp \
    OcctQtViewer.cpp \
    OcctQtWidget.cpp \
    libdraw/line.cpp \
    libdxfrw/drw_classes.cpp \
    libdxfrw/drw_entities.cpp \
    libdxfrw/drw_header.cpp \
    libdxfrw/drw_objects.cpp \
    libdxfrw/dx_iface.cpp \
    libdxfrw/examplewriter.cpp \
    libdxfrw/intern/drw_dbg.cpp \
    libdxfrw/intern/drw_textcodec.cpp \
    libdxfrw/intern/dwgbuffer.cpp \
    libdxfrw/intern/dwgreader.cpp \
    libdxfrw/intern/dwgreader15.cpp \
    libdxfrw/intern/dwgreader18.cpp \
    libdxfrw/intern/dwgreader21.cpp \
    libdxfrw/intern/dwgreader24.cpp \
    libdxfrw/intern/dwgreader27.cpp \
    libdxfrw/intern/dwgutil.cpp \
    libdxfrw/intern/dxfreader.cpp \
    libdxfrw/intern/dxfwriter.cpp \
    libdxfrw/intern/rscodec.cpp \
    libdxfrw/libdwgr.cpp \
    libdxfrw/libdxfrw.cpp \
    libdxfrw/libdxfrw_functions.cpp \
    libgcode/gcode_parser.cpp \
    libocct/draw_primitives.cpp \
    libscetcher/Geom2d_Arc.cxx \
    libscetcher/Geom2d_Edge.cxx \
    libscetcher/Sketcher.cxx \
    libscetcher/Sketcher_AnalyserSnap.cxx \
    libscetcher/Sketcher_Command.cxx \
    libscetcher/Sketcher_CommandArc3P.cxx \
    libscetcher/Sketcher_CommandArcCenter2P.cxx \
    libscetcher/Sketcher_CommandBezierCurve.cxx \
    libscetcher/Sketcher_CommandCircle2PTan.cxx \
    libscetcher/Sketcher_CommandCircle3P.cxx \
    libscetcher/Sketcher_CommandCircle3Tan.cxx \
    libscetcher/Sketcher_CommandCircleCenterRadius.cxx \
    libscetcher/Sketcher_CommandCircleP2Tan.cxx \
    libscetcher/Sketcher_CommandLine2P.cxx \
    libscetcher/Sketcher_CommandPoint.cxx \
    libscetcher/Sketcher_CommandTrim.cxx \
    libscetcher/Sketcher_GUI.cxx \
    libscetcher/Sketcher_Object.cxx \
    libscetcher/Sketcher_Property.cxx \
    libscetcher/Sketcher_PropertyArc.cxx \
    libscetcher/Sketcher_PropertyCircle.cxx \
    libscetcher/Sketcher_PropertyLine.cxx \
    libscetcher/Sketcher_PropertyPoint.cxx \
    libscetcher/Sketcher_QtGUI.cxx \
    libscetcher/Sketcher_Snap.cxx \
    libscetcher/Sketcher_SnapCenter.cxx \
    libscetcher/Sketcher_SnapEnd.cxx \
    libscetcher/Sketcher_SnapIntersection.cxx \
    libscetcher/Sketcher_SnapLine.cxx \
    libscetcher/Sketcher_SnapLineParallel.cxx \
    libscetcher/Sketcher_SnapLinePerpendicular.cxx \
    libscetcher/Sketcher_SnapMiddle.cxx \
    libscetcher/Sketcher_SnapNearest.cxx \
    libscetcher/Sketcher_SnapTangent.cxx \
    libspline/bezier_spline.cpp \
    libspline/cubic_spline.cpp \
    libspline/spline.cpp

HEADERS += \
    OcctQtControls.h \
    OcctQtFile.h \
    OcctQtFunctions.h \
    OcctQtMenu.h \
    OcctQtViewer.h \
    OcctQtWidget.h \
    libdraw/line.h \
    libdxfrw/drw_base.h \
    libdxfrw/drw_classes.h \
    libdxfrw/drw_entities.h \
    libdxfrw/drw_header.h \
    libdxfrw/drw_interface.h \
    libdxfrw/drw_objects.h \
    libdxfrw/dx_data.h \
    libdxfrw/dx_iface.h \
    libdxfrw/examplewriter.h \
    libdxfrw/intern/drw_cptable932.h \
    libdxfrw/intern/drw_cptable936.h \
    libdxfrw/intern/drw_cptable949.h \
    libdxfrw/intern/drw_cptable950.h \
    libdxfrw/intern/drw_cptables.h \
    libdxfrw/intern/drw_dbg.h \
    libdxfrw/intern/drw_textcodec.h \
    libdxfrw/intern/dwgbuffer.h \
    libdxfrw/intern/dwgreader.h \
    libdxfrw/intern/dwgreader15.h \
    libdxfrw/intern/dwgreader18.h \
    libdxfrw/intern/dwgreader21.h \
    libdxfrw/intern/dwgreader24.h \
    libdxfrw/intern/dwgreader27.h \
    libdxfrw/intern/dwgutil.h \
    libdxfrw/intern/dxfreader.h \
    libdxfrw/intern/dxfwriter.h \
    libdxfrw/intern/rscodec.h \
    libdxfrw/libdwgr.h \
    libdxfrw/libdxfrw.h \
    libdxfrw/libdxfrw_functions.h \
    libdxfrw/main_doc.h \
    libgcode/gcode_parser.h \
    libocct/draw_primitives.h \
    libscetcher/Geom2d_Arc.hxx \
    libscetcher/Geom2d_Edge.hxx \
    libscetcher/Sketcher.hxx \
    libscetcher/Sketcher_AnalyserSnap.hxx \
    libscetcher/Sketcher_Command.hxx \
    libscetcher/Sketcher_CommandArc3P.hxx \
    libscetcher/Sketcher_CommandArcCenter2P.hxx \
    libscetcher/Sketcher_CommandBezierCurve.hxx \
    libscetcher/Sketcher_CommandCircle2PTan.hxx \
    libscetcher/Sketcher_CommandCircle3P.hxx \
    libscetcher/Sketcher_CommandCircle3Tan.hxx \
    libscetcher/Sketcher_CommandCircleCenterRadius.hxx \
    libscetcher/Sketcher_CommandCircleP2Tan.hxx \
    libscetcher/Sketcher_CommandLine2P.hxx \
    libscetcher/Sketcher_CommandPoint.hxx \
    libscetcher/Sketcher_CommandTrim.hxx \
    libscetcher/Sketcher_GUI.hxx \
    libscetcher/Sketcher_Object.hxx \
    libscetcher/Sketcher_ObjectGeometryType.hxx \
    libscetcher/Sketcher_ObjectType.hxx \
    libscetcher/Sketcher_ObjectTypeOfMethod.hxx \
    libscetcher/Sketcher_OrthoType.hxx \
    libscetcher/Sketcher_Property.hxx \
    libscetcher/Sketcher_PropertyArc.hxx \
    libscetcher/Sketcher_PropertyCircle.hxx \
    libscetcher/Sketcher_PropertyLine.hxx \
    libscetcher/Sketcher_PropertyPoint.hxx \
    libscetcher/Sketcher_QtGUI.hxx \
    libscetcher/Sketcher_Snap.hxx \
    libscetcher/Sketcher_SnapCenter.hxx \
    libscetcher/Sketcher_SnapEnd.hxx \
    libscetcher/Sketcher_SnapIntersection.hxx \
    libscetcher/Sketcher_SnapLine.hxx \
    libscetcher/Sketcher_SnapLineParallel.hxx \
    libscetcher/Sketcher_SnapLinePerpendicular.hxx \
    libscetcher/Sketcher_SnapMiddle.hxx \
    libscetcher/Sketcher_SnapNearest.hxx \
    libscetcher/Sketcher_SnapTangent.hxx \
    libscetcher/Sketcher_SnapType.hxx \
    libspline/bezier_spline.h \
    libspline/cubic_spline.h \
    libspline/spline.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    OcctQtControls.ui \
    OcctQtFile.ui \
    OcctQtMenu.ui \
    OcctQtWidget.ui

RESOURCES += \
    libicon/icons.qrc


INCLUDEPATH +=D:\dev\occt-samples-qopenglwidget\OcctQtWidget\OcctQtLib\libdxfrw \
    D:\dev\occt-samples-qopenglwidget\OcctQtWidget\OcctQtLib\libeigen

INCLUDEPATH += D:\code\FITK\Tools\Win64\OCC\include 

LIBS+= -LD:\code\FITK\Tools\Win64\OCC\libd

LIBS += -lTKOffset -lTKQADraw -lopengl32


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

DISTFILES += \
    content_dump.txt \
    libdxfrw/main.txt \
    todo.txt

