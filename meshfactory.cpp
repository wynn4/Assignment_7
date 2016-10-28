//-------------------------------------------------------
// Filename: meshfactory.h
//
// Description:  A factory for creating triangle surface meshes
//               for a cube, cone and ellipse
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------

#include "meshfactory.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <QVector3D>
#include <QMatrix4x4>


void MeshGeometry3D::apply_transform(QMatrix4x4& transform)
{
    for(size_t id=0;id<mVerticies.size()/3;id++)
    {
        QVector4D p;
        p.setX(this->mVerticies[id*3]);
        p.setY(this->mVerticies[id*3+1]);
        p.setZ(this->mVerticies[id*3+2]);
        p.setW(1.0);

        p=transform*p;

        this->mVerticies[id*3]=p.x()/p.w();
        this->mVerticies[id*3+1]=p.y()/p.w();
        this->mVerticies[id*3+2]=p.z()/p.w();

    }
}

class MeshFactoryData
{
public:
    //Interal data and methods used to generate the mesh.
    MeshFactoryData(MeshGeometry3D *geometry);
    ~MeshFactoryData(){}

    size_t numberVerticies(){return geometry->mVerticies.size()/3;}
    QVector3D getVertex(int id);
    void setVertex(int id,QVector3D p);

    QVector3D getNormal(int id);

    int addVertex(QVector3D p);
    void scaleVerticies(double rx, double ry, double rz);
    void adjustSphereVerticies();

    void addIndex(QVector3D& tri);

    // return index of point in the middle of p1 and p2
    int getMiddlePoint(int p1, int p2);
    void refine_triangles(int refinement_level, std::vector<QVector3D>& faces);
    void calculate_normals(std::vector<QVector3D>& faces);

    int Index;
    MeshGeometry3D* geometry;
    std::map<int64_t, int> middlePointIndexCache;


};
MeshFactoryData::MeshFactoryData(MeshGeometry3D* geom)
{
    geometry=geom;
    Index=0;
}

MeshFactory::MeshFactory()
{

}
void MeshFactoryData::addIndex(QVector3D &tri)
{
    geometry->mIndicies.push_back(tri.x());
    geometry->mIndicies.push_back(tri.y());
    geometry->mIndicies.push_back(tri.z());
}


void MeshFactoryData::adjustSphereVerticies()
{
    //Push the sphere indicies out to the radius
    for(int i=0;i<Index;i++)
    {
        QVector3D p=getVertex(i);
        double length=p.length();
        p=p/length;
        setVertex(i,p);
    }
}

void MeshFactoryData::scaleVerticies(double rx,double ry,double rz)
{
    QMatrix4x4 scale;
    scale.scale(rx,ry,rz);
    for(int i=0;i<Index;i++)
    {
        QVector3D p=getVertex(i);
        p=scale*p;

        setVertex(i,p);
    }
}
// add vertex to mesh.
int MeshFactoryData::addVertex(QVector3D p)
{
    geometry->mVerticies.push_back(p.x());
    geometry->mVerticies.push_back(p.y());
    geometry->mVerticies.push_back(p.z());
    return Index++;
}
void MeshFactoryData::setVertex(int id,QVector3D p)
{
    geometry->mVerticies[id*3]=p.x();
    geometry->mVerticies[id*3+1]=p.y();
    geometry->mVerticies[id*3+2]=p.z();
}

QVector3D MeshFactoryData::getNormal(int id)
{
    QVector3D p;
    p.setX(geometry->mNormals[id*3]);
    p.setY(geometry->mNormals[id*3+1]);
    p.setZ(geometry->mNormals[id*3+2]);
    return p;
}
QVector3D MeshFactoryData::getVertex(int id)
{
    QVector3D p;
    p.setX(geometry->mVerticies[id*3]);
    p.setY(geometry->mVerticies[id*3+1]);
    p.setZ(geometry->mVerticies[id*3+2]);
    return p;
}



// return index of point in the middle of p1 and p2
int MeshFactoryData::getMiddlePoint(int p1, int p2)
{
    // first check if we have it already
    bool firstIsSmaller = p1 < p2;
    int64_t smallerIndex = firstIsSmaller ? p1 : p2;
    int64_t greaterIndex = firstIsSmaller ? p2 : p1;
    int64_t key = (smallerIndex << 32) + greaterIndex;


    std::map<int64_t, int>::iterator iter;
    iter=middlePointIndexCache.find(key);
    if (iter!=middlePointIndexCache.end())
    {
        return iter->second;
    }

    // not in cache, calculate it
    QVector3D point1 = getVertex(p1);
    QVector3D point2 = getVertex(p2);
    QVector3D middle(
        (point1.x() + point2.x()) / 2.0,
        (point1.y() + point2.y()) / 2.0,
        (point1.z() + point2.z()) / 2.0);

    // add vertex makes sure point is on unit sphere
    int i = addVertex(middle);

    // store it, return index
   middlePointIndexCache[key]=i;
    return i;
}
void MeshFactoryData::refine_triangles( int refinement_level,std::vector<QVector3D>& faces)
{
    // refine triangles by spliting the triangle into 4 triangles.
    for (int i = 0; i < refinement_level; i++)
    {
        std::vector<QVector3D> faces2;
        for(QVector3D tri : faces)
        {
            // replace triangle by 4 triangles
            int a = getMiddlePoint(tri.x(), tri.y());
            int b = getMiddlePoint(tri.y(), tri.z());
            int c = getMiddlePoint(tri.z(), tri.x());


            faces2.push_back( QVector3D(tri.x(), a, c));
            faces2.push_back( QVector3D(tri.y(), b, a));
            faces2.push_back( QVector3D(tri.z(), c, b));
            faces2.push_back( QVector3D(a, b, c));
        }
        faces = faces2;
    }
 }

void MeshFactoryData::calculate_normals(std::vector<QVector3D>& faces)
{
    //Calculate the normal of a vertex by averaging the normals of each triangles attached to the vertex

    //Create a list of triangles attached to each vertex
    std::map<int,std::vector<QVector3D>> vert_to_normal;
    for (QVector3D tri : faces)
    {
        QVector3D point1 = getVertex(tri.x());
        QVector3D point2 = getVertex(tri.y());
        QVector3D point3 = getVertex(tri.z());

        QVector3D normal = QVector3D::normal(point1,point2,point3);

        vert_to_normal[tri.x()].push_back(normal);
        vert_to_normal[tri.y()].push_back(normal);
        vert_to_normal[tri.z()].push_back(normal);

    }

    //Calculate the average normal of each triangle attached to a vertex
    for(int i=0;i<Index;i++)
    {
        QVector3D normal;
        for(int j=0;j<vert_to_normal[i].size();j++)
        {
            normal+=vert_to_normal[i][j];
        }
        normal/=vert_to_normal[i].size();

        geometry->mNormals.push_back(normal.x());
        geometry->mNormals.push_back(normal.y());
        geometry->mNormals.push_back(normal.z());
    }

}

void MeshFactory::GenerateEllipsoidMesh(double rx,double ry, double rz,int refinement_level, MeshGeometry3D* geometry)
{
    //Based http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
    //by Andreas Kahler.

    MeshFactoryData data(geometry);
    std::vector<QVector3D> faces;
    // create 12 vertices of a icosahedron
    double t = (1.0 + sqrt(5.0)) / 2.0;

    data.addVertex(QVector3D(-1,  t,  0));
    data.addVertex(QVector3D( 1,  t,  0));
    data.addVertex(QVector3D(-1, -t,  0));
    data.addVertex(QVector3D( 1, -t,  0));

    data.addVertex(QVector3D( 0, -1,  t));
    data.addVertex(QVector3D( 0,  1,  t));
    data.addVertex(QVector3D( 0, -1, -t));
    data.addVertex(QVector3D( 0,  1, -t));

    data.addVertex(QVector3D( t,  0, -1));
    data.addVertex(QVector3D( t,  0,  1));
    data.addVertex(QVector3D(-t,  0, -1));
    data.addVertex(QVector3D(-t,  0,  1));


    // create 20 triangles of the icosahedron


    // 5 faces around point 0
    faces.push_back( QVector3D(0, 11, 5));
    faces.push_back( QVector3D(0, 5, 1));
    faces.push_back( QVector3D(0, 1, 7));
    faces.push_back( QVector3D(0, 7, 10));
    faces.push_back( QVector3D(0, 10, 11));

    // 5 adjacent faces
    faces.push_back( QVector3D(1, 5, 9));
    faces.push_back( QVector3D(5, 11, 4));
    faces.push_back( QVector3D(11, 10, 2));
    faces.push_back( QVector3D(10, 7, 6));
    faces.push_back( QVector3D(7, 1, 8));

    // 5 faces around point 3
    faces.push_back( QVector3D(3, 9, 4));
    faces.push_back( QVector3D(3, 4, 2));
    faces.push_back( QVector3D(3, 2, 6));
    faces.push_back( QVector3D(3, 6, 8));
    faces.push_back( QVector3D(3, 8, 9));

    // 5 adjacent faces
    faces.push_back( QVector3D(4, 9, 5));
    faces.push_back( QVector3D(2, 4, 11));
    faces.push_back( QVector3D(6, 2, 10));
    faces.push_back( QVector3D(8, 6, 7));
    faces.push_back( QVector3D(9, 8, 1));


    data.refine_triangles( refinement_level,faces);

    data.adjustSphereVerticies();

    data.scaleVerticies(rx,ry,rz);

    // done, now add triangles to mesh
    for (QVector3D tri : faces)
    {
        data.addIndex(tri);
    }

    data.calculate_normals(faces);

}


void MeshFactory::GenerateCubeMesh(double width, double height,double depth, int refinement_level, MeshGeometry3D* geometry)
{
    MeshFactoryData data(geometry);
    std::vector<QVector3D> faces;


    data.addVertex(QVector3D(.5,  -.5,  .5));//0
    data.addVertex(QVector3D(.5,.5,.5));//1
    data.addVertex(QVector3D(-.5,.5,.5));//2
    faces.push_back( QVector3D(0,1,2));

    data.addVertex(QVector3D(.5,  -.5,  .5));//3
    data.addVertex(QVector3D(-.5,.5,.5));//4
    data.addVertex(QVector3D(-.5,-.5,.5));//5
    faces.push_back( QVector3D(3,4,5));

    data.addVertex(QVector3D(.5,.5,.5));//6
    data.addVertex(QVector3D(.5,.5,-.5));//7
    data.addVertex(QVector3D(-.5,.5,-.5));//8
    faces.push_back( QVector3D(6,7,8));


    data.addVertex(QVector3D(.5,.5,.5));//9
    data.addVertex(QVector3D(-.5,.5,-.5));//10
    data.addVertex(QVector3D(-.5,.5,.5));//11
    faces.push_back( QVector3D(9,10,11));

    data.addVertex(QVector3D(.5,.5,-.5));//12
    data.addVertex(QVector3D(.5,-.5,-.5));//13
    data.addVertex(QVector3D(-.5,-.5,-.5));//14
    faces.push_back( QVector3D(12,13,14));


    data.addVertex(QVector3D(.5,.5,-.5));//15
    data.addVertex(QVector3D(-.5,-.5,-.5));//16
    data.addVertex(QVector3D(-.5,.5,-.5));//17
    faces.push_back( QVector3D(15,16,17));

    data.addVertex(QVector3D(.5,-.5,-.5));//18
    data.addVertex(QVector3D(.5,-.5,.5));//19
    data.addVertex(QVector3D(-.5,-.5,.5));//20
    faces.push_back( QVector3D(18,19,20));


    data.addVertex(QVector3D(.5,-.5,-.5));//21
    data.addVertex(QVector3D(-.5,-.5,.5));//22
    data.addVertex(QVector3D(-.5,-.5,-.5));//23
    faces.push_back( QVector3D(21,22,23));


    data.addVertex(QVector3D(-.5,-.5,-.5));//24
    data.addVertex(QVector3D(-.5,-.5,.5));//25
    data.addVertex(QVector3D(-.5,.5,.5));//26
    faces.push_back( QVector3D(24,25,26));

    data.addVertex(QVector3D(-.5,-.5,-.5));//27
    data.addVertex(QVector3D(-.5,.5,.5));//28
    data.addVertex(QVector3D(-.5,.5,-.5));//29
    faces.push_back( QVector3D(27,28,29));


    data.addVertex(QVector3D(.5,.5,.5));//30
    data.addVertex(QVector3D(.5,  -.5,  .5));//31
    data.addVertex(QVector3D(.5,-.5,-.5));//32
    faces.push_back( QVector3D(30,31,32));

    data.addVertex(QVector3D(.5,.5,.5));//33
    data.addVertex(QVector3D(.5,-.5,-.5));//34
    data.addVertex(QVector3D(.5,.5,-.5));//35
    faces.push_back( QVector3D(33,34,35));


    data.refine_triangles( refinement_level,faces);

    data.scaleVerticies(width,height,depth);


    // done, now add triangles to mesh
    for (QVector3D tri : faces)
    {
        data.addIndex(tri);
    }
    data.calculate_normals(faces);
}

void MeshFactory::GenerateConeMesh(double rx, double ry, double height, int divisions, MeshGeometry3D* geometry)
{
    if(divisions<3)
        return;
    MeshFactoryData data(geometry);

    double rad=2*M_PI/divisions;

    std::vector<QVector3D> faces;

    int v=data.addVertex(QVector3D(0,  0,  0));
    int v0=data.addVertex(QVector3D(.5,  0,  0));
    int v1=v0;

    for(int i=1;i<divisions;i++)
    {
        double rx=.5*cos(rad*i);
        double ry=.5*sin(rad*i);
        int v2= data.addVertex(QVector3D(rx,  ry,  0));
        int v3=data.addVertex(QVector3D( 0,  0, 1));

        faces.push_back( QVector3D(v1,v2, v3));
        faces.push_back( QVector3D(v2,v1, v));
        v1=v2;
    }
    int v3=data.addVertex(QVector3D( 0,  0, 1));
    faces.push_back( QVector3D(v1,v0, v3));
    faces.push_back( QVector3D(v0,v1, v));

    data.scaleVerticies(rx,ry,height);


    for (QVector3D tri : faces)
    {
        data.addIndex(tri);
    }
    data.calculate_normals(faces);

}




