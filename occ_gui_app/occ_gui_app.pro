QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OcctQtViewer.cpp \
    OcctQtcontrols.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    OcctQtViewer.h \
    OcctQtcontrols.h \
    mainwindow.h

FORMS += \
    OcctQtcontrols.ui \
    mainwindow.ui

# Occt inludes
LIBS += -L/usr/local/lib/

INCLUDEPATH +=  /usr/local/include/opencascade/ \
                /usr/include/ \
                /usr/local/lib/

# OCCT libraries to link
LIBS += -lTKernel -lTKGeomBase -lTKGeomAlgo -lTKG2d -lTKV3d -lTKG3d  -lTKHLR -lTKService -lTKMath -lTKBRep -lTKTopAlgo -lTKOpenGl -lTKPrim -lTKShHealing -lTKMesh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    libicon/icons.qrc
