#ifndef INTERFACE_H
#define INTERFACE_H

#include "QWidget"
#include "iostream"
#include "vector"
#include "gp_Pnt.hxx"
#include "LineLineIntersect.h"
#include "LineArcIntersect.h"
#include "ArcCenter.h"
#include <ArcPoints.h>

//! Epsilon.
#define EPS 0.001

enum MSG{
    zero,
    ok,
    point_is_duplicate
};

enum TYPE{
    none,
    point,
    line,
    rectangle,
    polyline,
    polygon,
    hexagon,
    arc_cp_2p,
    arc_3p,
    circle_cp_2p,
    circle_3p,
    ellipse,
    spline,
    bezier,
    slot,
    arrow,
    //! 3DSOLIDS
    sphere,
    box,
};

enum LINETYPE{
    continious,
    dashed_center,
    dashed_dot,
    dashed_even
};

struct COLOR{
    //! Range 0-255.
    unsigned int red=0, green=0, blue=0, alpha=0;
};

struct PROPERTIES{
private:
    int myLayer=0;
    LINETYPE myLinetype;
    double myLinewidht=0;
    //! Color 0-255
    COLOR myColor;

public:
    void setLayer(int theLayer){
        myLayer=theLayer;
    }
    void setLineType(LINETYPE theType){
        myLinetype=theType;
    }
    void setLineWidth(double theLinewidht){
        myLinewidht=theLinewidht;
    }
    void setColor(double red, double green, double blue, double alpha){
        myColor.red=red;
        myColor.green=green;
        myColor.blue=blue;
        myColor.alpha=alpha;
    }
    void setColor(COLOR theColor){
        myColor=theColor;
    }
};

struct VALUES{
private:
    //! pvec[0]=first point for line or arc.
    //! pvec[1]=second point for line or arc.
    //! pvec[2]=third point for arc.
    std::vector<gp_Pnt> pvec;
    //! dvec[0]=radius
    std::vector<double> dvec;
public:
    void setPointVectorSize(size_t theSize){
        pvec.resize(theSize);
    }
    //! Used to store values like radius.
    void setDoubleVectorSize(size_t theSize){
        dvec.resize(theSize);
    }
    void clear(){
        pvec.clear();
        dvec.clear();
    }
    void setPointValues(int theIndex, gp_Pnt thePoint){
        pvec.at(theIndex)=thePoint;
    };
    void setPointValues(std::vector<gp_Pnt> thePoints){
        pvec=thePoints;
    }
    void setRadius(double radius){
        dvec[0]=radius;
    }
    bool isDuplicate(gp_Pnt thePoint){
        for(unsigned int i=0; i<pvec.size(); i++){
            if(thePoint.Distance(pvec.at(i))<EPS){
                return 1;
            }
        }
        return 0;
    }
    gp_Pnt getFirstPoint(){
        return pvec.at(0);
    }
    gp_Pnt getSecondPoint(){
        return pvec.at(1);
    }
    gp_Pnt getThrirdPoint(){
        return pvec.at(2);
    }
    double getRadius(){
        return dvec.at(0);
    }
    gp_Pnt getArcCenter(){
        return ArcCenter(pvec[0],pvec[1],pvec[2]).Arc_cp();
    }
};

class OBJECT{
public:
    OBJECT(){}
    virtual ~OBJECT(){}

    void setDebug(bool state){
        myDebug=state;
    }
    void setType(TYPE theType){
        myType=theType;
        setTypeValueModel();
    };
    TYPE getType(){
        return myType;
    }
    void setProperties(PROPERTIES properties){
        myProperties=properties;
    };
    void setColor(COLOR theColor){
        myProperties.setColor(theColor);
    }
    //! Range 0-255
    void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha){
        myProperties.setColor(red,green,blue,alpha);
    }
    void setLineType(LINETYPE theLinetype){
        myProperties.setLineType(theLinetype);
    }
    void setLineWidht(double theLineWidth){
        myProperties.setLineWidth(theLineWidth);
    }
    void setLayer(int theLayer){
        myProperties.setLayer(theLayer);
    }

    PROPERTIES getProperties(){
        return myProperties;
    }
    //! setPoints{0,{0,0,0}}
    void setPoints(unsigned int theIndex, gp_Pnt thePoint){
        myValues.setPointValues(theIndex,thePoint);
    };
    //! setPoints{{0,0,0},{0,0,0}}
    void setPoints(std::vector<gp_Pnt> thePoints){
        myValues.setPointValues(thePoints);
    };
    void setRadius(double radius){
        myValues.setRadius(radius);
    }
    VALUES getValues(){
        return myValues;
    }
    void matchType(OBJECT theRefObject){
        myType=theRefObject.myType;
    };
    void matchProperties(OBJECT theRefObject){
        myProperties=theRefObject.myProperties;
    };
    void matchValues(OBJECT theRefObject){
        myValues=theRefObject.myValues;
    };
    void matchEverything(OBJECT theRefObject){
        myType=theRefObject.myType;
        myProperties=theRefObject.myProperties;
        myValues=theRefObject.myValues;
    };
    bool getIntersections(OBJECT theRefObject, std::vector<gp_Pnt> &pvec){

        //! Line-line 3d intersection
        if(myType==TYPE::line && theRefObject.myType==TYPE::line){
            bool result=LineLineIntersect(this->getValues().getFirstPoint(),
                              this->getValues().getSecondPoint(),
                              theRefObject.getValues().getFirstPoint(),
                              theRefObject.getValues().getSecondPoint()).getIntersections(pvec);
            return result;
        };

        //! Arc-line 3d intersection and visa-versa
        if(myType==TYPE::line && theRefObject.myType==TYPE::arc_3p){
            bool result=LineArcIntersect(this->getValues().getFirstPoint(),
                                         this->getValues().getSecondPoint(),
                                         theRefObject.getValues().getArcCenter(),
                                         theRefObject.getValues().getRadius()).getIntersections(pvec);
            return result;
        };
        if(myType==TYPE::arc_3p && theRefObject.myType==TYPE::line){
            bool result=LineArcIntersect(theRefObject.getValues().getFirstPoint(),
                                         theRefObject.getValues().getSecondPoint(),
                                         this->getValues().getArcCenter(),
                                         this->getValues().getRadius()).getIntersections(pvec);
            return result;
        };

        //! Arc-arc 3d intersection


        return 0;
    };

private:
    bool myDebug;
    TYPE myType;
    PROPERTIES myProperties;
    VALUES myValues;

    void setTypeValueModel(){
        if(myType==TYPE::point){
            myValues.setPointVectorSize(1);
        };
        if(myType==TYPE::line){
            myValues.setPointVectorSize(2);
        };
        if(myType==TYPE::arc_cp_2p || myType==TYPE::arc_3p || myType==TYPE::circle_3p || myType==TYPE::circle_cp_2p){
            myValues.setPointVectorSize(3);
            //! Radius
            myValues.setDoubleVectorSize(1);
        };
        if(myType==TYPE::rectangle){
            myValues.setPointVectorSize(4);
        };
        if(myDebug){
            std::cout<<"Type:"<<myType<<std::endl;
        }
    };
};

#endif // INTERFACE_H





















