QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET=occ_gui_app_mainwindow

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OcctQtControl.cpp \
    OcctQtViewer.cpp \
    Tranceparancy.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ArcCenter.h \
    ArcPoints.h \
    Interface.h \
    LineArcIntersect.h \
    LineLineIntersect.h \
    OcctQtControl.h \
    OcctQtViewer.h \
    PointOnLine.h \
    Tranceparancy.h \
    Vector3D.h \
    mainwindow.h

FORMS += \
    OcctQtControl.ui \
    Tranceparancy.ui \
    mainwindow.ui

win32 {
INCLUDEPATH +=D:\dev\occt-samples-qopenglwidget\OcctQtWidget\OcctQtLib\libdxfrw \
    D:\dev\occt-samples-qopenglwidget\OcctQtWidget\OcctQtLib\libeigen \

INCLUDEPATH += D:\code\FITK\Tools\Win64\OCC\include

LIBS+= -LD:\code\FITK\Tools\Win64\OCC\lib \
       -LD:\code\FITK\Tools\Win64\OCC\libd

LIBS += -lTKOffset -lTKQADraw -lopengl32

}

unix {
# Opencascade
INCLUDEPATH += /opt/opencascade/oce-upstream-V7_5_0beta/inc \
               /opt/opencascade/oce-upstream-V7_5_0beta/src
LIBS+= -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/lib \
       -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/libd

INCLUDEPATH +=  /usr/include/ \
                /usr/local/lib/
}

# OCCT libraries to link
LIBS +=  -lTKernel -lTKGeomBase -lTKGeomAlgo -lTKG2d -lTKV3d -lTKG3d  -lTKHLR -lTKService -lTKMath -lTKBRep -lTKTopAlgo -lTKOpenGl -lTKPrim -lTKShHealing -lTKMesh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    libicon/icons.qrc

DISTFILES += \
    readme.md
