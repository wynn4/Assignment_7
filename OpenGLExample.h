//-------------------------------------------------------
// Filename: OpenGLExample.h
//
// Description:  A Qt5 opengl window
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------

#ifndef OPENGLEXAMPLE_H
#define OPENGLEXAMPLE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QKeyEvent>
class MeshGeometry3D;


class OpenGLExample : public QOpenGLWidget, protected QOpenGLFunctions
{
  public:
    OpenGLExample( QWidget *parent=0 );
    ~OpenGLExample();


  protected:
    void initializeGL(void);
    void resizeGL( int w, int h );
    void paintGL();
    void keyPressEvent( QKeyEvent *e);
    void timerEvent(QTimerEvent*);

   private:
    QOpenGLShaderProgram mShaderProgram;
    GLuint mProgramHandle;
    GLuint mMVPMatrixUHandle;
    GLuint mMVMatrixUHandle;
    GLuint mLightPositionUHandle;
    GLuint mColorUHandle;
    GLuint mPositionAHandle;
    GLuint mNormalAHandle;
    GLuint mVertexBufferHandle;
    GLuint mIndexBufferHandle;
    GLuint mNormalBufferHandle;

    int64_t mNumIndicies;
    QMatrix4x4 mMVP;
    QMatrix4x4 mMV;
    QMatrix4x4 mProjectionMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mRotate;


    int mWidth;
    int mHeight;
    QVector3D mLightPos;
    GLfloat mMaxCoord;
    int mTimerCount;
    QVector3D mRotateAxis;
};


#endif // OPENGLEXAMPLE_H
