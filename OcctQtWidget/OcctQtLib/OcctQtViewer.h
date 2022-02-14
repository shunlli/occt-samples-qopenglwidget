// Copyright (c) 2021 OPEN CASCADE SAS
//
// This file is part of the examples of the Open CASCADE Technology software library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

//! Edited by Skynet Cyberdyne 01-2022.

#ifndef _OcctQtViewer_HeaderFile
#define _OcctQtViewer_HeaderFile

#include <Standard_WarningsDisable.hxx>
#include <QOpenGLWidget>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
#include <Poly.hxx>

#include <libscetcher/Sketcher.hxx>

//! OCCT 3D View.
class OcctQtViewer : public QOpenGLWidget, public AIS_ViewController
{
  Q_OBJECT

public:

  //! Main constructor.
  OcctQtViewer (QWidget* theParent = nullptr);

  //! Destructor.
  virtual ~OcctQtViewer();

  //! Return Viewer.
  const Handle(V3d_Viewer)& Viewer() const { return myViewer; }

  //! Return View.
  const Handle(V3d_View)& View() const { return myView; }

  //! Return AIS context.
  const Handle(AIS_InteractiveContext)& Context() const { return myContext; }

  //! Return OpenGL info.
  const QString& getGlInfo() const { return myGlInfo; }

  //! Minial widget size.
  //virtual QSize minimumSizeHint() const override { return QSize(200, 200); }

  //! Default widget size.
  //virtual QSize sizeHint()        const override { return QSize(720, 480); }

  //! Set the tranceparancy level of the shapevec.
  void set_tranceparancy(opencascade::handle<AIS_Shape> shape, double value);

  //! Set the background color. Red,green,blue. 0-255.
  void set_backgroundcolor(double r, double g, double b);

  //! Enable the shape contours lines to be viewed.
  void show_boundary(Handle(AIS_Shape) shape);
  void hide_boundary(Handle(AIS_Shape) shape);

  //! Show or hide the navigation cube.
  void show_cube();
  void hide_cube();

  //! Shape preview mode.
  void show_as_wireframe(Handle(AIS_Shape) shape);
  void show_as_shaded(Handle(AIS_Shape) shape);

  //! Triedron axis origin.
  void show_triedron();
  void hide_triedron();

  //! Display mode.
  void set_orthographic();
  void set_perspective();

  //! A bucket containing all shapes.
  std::vector<Handle(AIS_Shape)> aShapeVec;

  //! A shape that is displayed during contruction of a primitive.
  //! It displays the mouse startpos and updates current mousepos to next to press primitive point.
  bool mode_construct_line=0;
  unsigned int count=0;
  Handle(AIS_Shape) AisConstructShape, AisPlane, AisSnapSphere;

  //! 3d mousepos coordinates from occt diplay.
  gp_Pnt mousepos;

  //! Show a shapevec or stepfile.
  void show_shapevec(std::vector<Handle(AIS_Shape)> shapevec);

  //! Show a single shape.
  void show_shape(Handle(AIS_Shape) shape);

  //! Redisplay a shape.
  void remove_shape(Handle(AIS_Shape) shape);

  void redraw();

  bool mode_ortho=0;
  bool mode_snap=0;
  double snap_dist=2.0;
  gp_Pnt snap_pos;
  gp_Pnt p0,p1;

  Sketcher *mySketcher;

signals:
    void mouse_signal();
    void F3(bool checked);
    void F8(bool checked);

protected: // OpenGL events

  virtual void initializeGL() override;
  virtual void paintGL() override;
  //virtual void resizeGL(int , int ) override;

protected: // user input events

  virtual void closeEvent       (QCloseEvent*  theEvent) override;
  virtual void keyPressEvent    (QKeyEvent*    theEvent) override;
  virtual void mousePressEvent  (QMouseEvent*  theEvent) override;
  virtual void mouseReleaseEvent(QMouseEvent*  theEvent) override;
  virtual void mouseMoveEvent   (QMouseEvent*  theEvent) override;
  virtual void wheelEvent       (QWheelEvent*  theEvent) override;

private:

  //! Dump OpenGL info.
  void dumpGlInfo (bool theIsBasic);

  //! Request widget paintGL() event.
  void updateView();

  //! Handle view redraw.
  virtual void handleViewRedraw (const Handle(AIS_InteractiveContext)& theCtx,
                                 const Handle(V3d_View)& theView) override;

private:
  Handle(V3d_Viewer)             myViewer;
  Handle(V3d_View)               myView;
  Handle(AIS_InteractiveContext) myContext;
  Handle(AIS_ViewCube)           myViewCube;

  GLint m_vaoHandle;
  QString myGlInfo;
  bool myIsCoreProfile;

  //! Sketcher vars.
  double aVx, aVy, aVz;
  double aPx, aPy, aPz;


};

#endif // _OcctQtViewer_HeaderFile
