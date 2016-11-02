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
#ifndef MESHFACTORY_H
#define MESHFACTORY_H
#include <map>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>

class MeshGeometry3D
{
public:
    std::vector<GLfloat> mVerticies;
    std::vector<GLfloat> mNormals;
    std::vector<GLuint> mIndicies;

    GLfloat Color[3];

    void apply_transform(QMatrix4x4& transform);
};


class MeshFactory
{
public:
    MeshFactory();
    void GenerateEllipsoidMesh(double rx, double ry, double rz, int refinement_level, MeshGeometry3D *geometry);
    void GenerateCubeMesh(int width, int height, int depth, int refinement_level, MeshGeometry3D *geometry);
    void GenerateConeMesh(double rx, double ry, double height, int divisions, MeshGeometry3D *geometry);

private:


};


#endif // MESHFACTORY_H
