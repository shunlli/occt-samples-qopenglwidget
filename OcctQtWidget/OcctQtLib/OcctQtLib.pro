QT += widgets gui opengl

TEMPLATE = lib
DEFINES += OCCTQT_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OcctQtControls.cpp \
    OcctQtViewer.cpp \
    OcctQtWidget.cpp

HEADERS += \
    OcctQtControls.h \
    OcctQtViewer.h \
    OcctQtWidget.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    OcctQtControls.ui \
    OcctQtWidget.ui

RESOURCES += \
    libicon/icons.qrc

# Occt includes
LIBS += -L/usr/local/lib/

INCLUDEPATH +=  /usr/local/include/opencascade/ \
                /usr/include/ \
                /usr/local/lib/

# OCCT libraries to link
LIBS += -lTKernel -lTKGeomBase -lTKGeomAlgo -lTKG2d -lTKV3d -lTKG3d  -lTKHLR -lTKService -lTKMath -lTKBRep -lTKTopAlgo -lTKOpenGl -lTKPrim -lTKShHealing -lTKMesh
