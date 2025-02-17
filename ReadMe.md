These sample's demonstrates how to use Open CASCADE Technology (OCCT) 3D Viewer within a 

window created using Qt5 on Windows and Linux platforms.

Opencascade libary download : https://github.com/grotius-cnc/occt-samples-qopenglwidget/releases/download/1.1/opencascade.tar.gz

Unpack it in ~/opt/ That it looks like ~/opt/opencascade/ etc.

OpenGL-based OCCT viewer is embedded into Qt5 Widgets application via `QOpenGLWidget` widget.


OCCT QOpenGLWidget sample. QWidget library
-----------------

![sketcher](https://user-images.githubusercontent.com/44880102/153814934-ec056b93-3ae5-4cae-a5cd-3612d3e7ad14.jpg)
![gui_preview](https://user-images.githubusercontent.com/44880102/151472889-d7c74424-c67c-4d27-86bb-47ac6700d3d9.jpg)

    Specs:
    - C++ Library.
    - QWidget.
    - Some sketcher functions, wich i find helpfull but incomplete related to autodesk input method's.
 
OCCT QOpenGLWidget sample. Gui designer widget coding.
------------------

![occt_widget](https://user-images.githubusercontent.com/44880102/151247897-0e7f69ef-58fa-453a-8ffb-3e2d0e3b8838.jpg)

    Specs:
    - Xyz mouse coordinates mapped to the occt environment.
    - Transparant qt widget overlay.
    - Viewports, 3d, top, bottom, left, right, front, back.
    - Zoom to fit, zoom +, zoom -
    - Create a shape and set tranceparancy level.
    - Show shapes as wireframe or as shaded object.
    - Show or hide 3d navigation cube.
    - Show or hide triedron.
    - Show shape in orthographic or perspective mode.
    - Show or hide shape boundary lines.
    - Print the actual opencascade performance
    
OCCT QOpenGLWidget sample. Parametric widget coding.
--------------------

![occt-qopenglwidget-sample-wnt](https://user-images.githubusercontent.com/44880102/151248072-c18aebc2-86af-4cc6-9bfa-e6a94649db45.png)

    Specs:
    - Transparant qt widget overlay.
    - Rotate view with navigation cube.
    - Zoom with mouse.
    - Show shapes as shaded object.
    - Shows 3d navigation cube
    - Shows triedron.
    - Print the actual opencascade performance
