#include "arccenter.h"

arccenter::arccenter()
{

}

/**
 * @brief estimate the center and the radious of a circle in 3D given 3 points
 * This is the relevant function
 */
void arccenter::circlecenter3d(gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt &cp, double &radius, double &arc_angle)
{

    //! Converse point to vector.
    Vector3D vp1,vp2,vp3,vcp;
    vp1.x=p1.X();
    vp1.y=p1.Y();
    vp1.z=p1.Z();

    vp2.x=p2.X();
    vp2.y=p2.Y();
    vp2.z=p2.Z();

    vp3.x=p3.X();
    vp3.y=p3.Y();
    vp3.z=p3.Z();

    // https://stackoverflow.com/questions/13977354/build-circle-from-3-points-in-3d-space-implementation-in-c-or-c
    Vector3D v1 = vp2-vp1;
    Vector3D v2 = vp3-vp1;
    double v1v1, v2v2, v1v2;
    v1v1 = v1.dot(v1);
    v2v2 = v2.dot(v2);
    v1v2 = v1.dot(v2);

    float base = 0.5/(v1v1*v2v2-v1v2*v1v2);
    float k1 = base*v2v2*(v1v1-v1v2);
    float k2 = base*v1v1*(v2v2-v1v2);
    vcp = vp1 + v1*k1 + v2*k2; // center

    radius = (vcp-vp1).norm();

    //! Center point result from vector to point.
    cp.SetX(vcp.x);
    cp.SetY(vcp.y);
    cp.SetZ(vcp.z);

    //! Now we got the circle center, we can calculate arc angle from p1 to p3.
    Vector3D v3 = vp2-vp1;
    Vector3D v4 = vp3-vp1;

    arc_angle= std::acos(v3.dot(v4)/(v3.magnitude()*v4.magnitude()));

    //! Normalize v3:
    double l=sqrt((v3.x*v3.x)+(v3.y*v3.y)+(v3.z*v3.z));
    v3.x=v3.x/l;
    v3.y=v3.y/l;
    v3.z=v3.z/l;
    std::cout<<"v3 normalized x:"<<v3.x<<" y:"<<v3.y<<" z:"<<v3.z<<std::endl;

    //! Normalize v4:
    l=sqrt((v4.x*v4.x)+(v4.y*v4.y)+(v4.z*v4.z));
    v4.x=v4.x/l;
    v4.y=v4.y/l;
    v4.z=v4.z/l;
    std::cout<<"v4 normalized x:"<<v4.x<<" y:"<<v4.y<<" z:"<<v4.z<<std::endl;

    //! Crossproduct v3 & v4.
    Vector3D res;
    res.x=(v3.y*v4.z)-(v3.z*v4.y);
    res.y=(v3.z*v4.x)-(v3.x*v4.z);
    res.z=(v3.x*v4.y)-(v3.y*v4.x);

    //! Normalize res:
    l=sqrt((res.x*res.x)+(res.y*res.y)+(res.z*res.z));
    res.x=res.x/l;
    res.y=res.y/l;
    res.z=res.z/l;
    std::cout<<"crossproduct res x:"<<res.x<<" y:"<<res.y<<" z:"<<res.z<<std::endl;

    Vector3D xy_normal(0, 0, 1);
}
