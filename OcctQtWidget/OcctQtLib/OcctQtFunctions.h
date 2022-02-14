#ifndef OCCTQTFUNCTIONS_H
#define OCCTQTFUNCTIONS_H

#include <QString>

// Libocct
#include <AIS_Shape.hxx>
#include <TDF_Label.hxx>
#include <XCAFDoc_ColorTool.hxx>

// libdxfrw
#include <libdxfrw_functions.h>


class OcctQtFunctions
{
public:
    OcctQtFunctions();

    Handle(XCAFDoc_ColorTool) aColorTool;
    Handle(XCAFDoc_ShapeTool) aShapeTool;
    std::vector<Handle(AIS_Shape)> Ais_ShapeVec;

    std::vector<Handle(AIS_Shape)> load_stepfile(QString filename);
    void Visit(const TDF_Label& theLabel);

    std::vector<Handle(AIS_Shape)> load_dxffile(QString filename);
    std::vector<Handle(AIS_Shape)> load_ngcfile(QString filename);
    std::vector<Handle(AIS_Shape)> load_stlfile(QString filename);
};

#endif // OCCTQTFUNCTIONS_H
