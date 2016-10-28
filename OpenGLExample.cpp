//-------------------------------------------------------
// Filename: OpenGLExample.cpp
//
// Description:  The cpp file for the qt5 opengl shape example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------
#include "OpenGLExample.h"

// Include standard headers
#include <QApplication>
#include <QOpenGLTexture>
#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <QtMath>
#include <random>


#include "meshfactory.h"
static int timer_interval = 100;        // timer interval (millisec)


OpenGLExample::OpenGLExample( QWidget *parent ) : QOpenGLWidget(parent)
{
    startTimer( timer_interval );
    mMaxCoord=4;
    mProgramHandle=0;

    mPositionAHandle=0;
    mNormalAHandle=0;
    mVertexBufferHandle=0;
    mIndexBufferHandle=0;
    mNormalBufferHandle=0;

    mMVPMatrixUHandle=0;
    mMVMatrixUHandle=0;
    mLightPositionUHandle=0;
    mColorUHandle=0;
    mTimerCount=0;
    mRotateAxis.setX(1);
    mRotateAxis.setY(1);
}

OpenGLExample::~OpenGLExample()
{
    // Cleanup VBO and shader
    makeCurrent();
    glDeleteBuffers(1, &mVertexBufferHandle);
    glDeleteBuffers(1, &mNormalBufferHandle);
    glDeleteProgram(mProgramHandle);

}

void OpenGLExample::initializeGL()
{
    // initialize OpenGL
    initializeOpenGLFunctions();

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.6f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    bool success;
    //*** Shader Section ***
    //load and compile vertex shader
    success = mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                    ":/VertexShader.vert");

    // load and compile fragment shader
    success = mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                    ":/FragmentShader.frag");
    //Link our shaders
    mShaderProgram.link();

    //*** Variable Handle Section ***
    //Get the shader program handle
    mProgramHandle = mShaderProgram.programId();

    //Remember that the name inside the " " is the name of the variable in the shader program.
    //Look in VertexShader.vert for the variable u_MVPMatrix.

    // Get a handle for our "u_MVPMatrix" uniform
    mMVPMatrixUHandle = glGetUniformLocation(mProgramHandle, "u_MVPMatrix");
    // Get a handle for our "u_MVMatrix" uniform
    mMVMatrixUHandle = glGetUniformLocation(mProgramHandle, "u_MVMatrix");

    // Get a handle for our "u_LightPos" uniform
    mLightPositionUHandle = glGetUniformLocation(mProgramHandle, "u_LightPos");

    // Get a handle for our "u_Color" uniform
    mColorUHandle = glGetUniformLocation(mProgramHandle, "u_Color");


    // Get a handle for our "a_Position" attribute
    mPositionAHandle = glGetAttribLocation(mProgramHandle, "a_Position");

    // Get a handle for our "a_Normal" attribute
    mNormalAHandle = glGetAttribLocation(mProgramHandle, "a_Normal");

    //*** Geometry Mesh Generation Section  ***
    //Create the triangle mesh for our basic shapes
    MeshGeometry3D ellipsoid;
    MeshGeometry3D cone;
    MeshGeometry3D cube;

    std::vector<MeshGeometry3D*> all_geometry;
    //Create the mesh factory
    MeshFactory factory;

    //Create a mesh for a ellipsoid
    factory.GenerateEllipsoidMesh(1.5,1,.75,2,&ellipsoid);
    //Create the model matrix for the model transformations
    QMatrix4x4 EM;
    EM.translate(0,4,0);
    //transform the ellipsoid
    ellipsoid.apply_transform(EM);
    //Add the ellipsoid mesh to our list of all geometry
    all_geometry.push_back(&ellipsoid);

    //Create mesh for a cube.
    factory.GenerateCubeMesh(1,1,1,0,&cube);
    //transform the cube
    QMatrix4x4 CM;
    CM.translate(0,-4,0);
    cube.apply_transform(CM);
    //Add the cube mesh to our list of all geometry
    all_geometry.push_back(&cube);

    //Create a mesh for cone
    factory.GenerateConeMesh(2,2,3,75,&cone);
    //We aren't going to transform our cone.  We will leave it where the meshfactory created it.
    //Add the cone mesh to our list of all geometry
    all_geometry.push_back(&cone);


    //*** Prepare the geometry mesh to be passed to opengl  ***
    std::vector<GLfloat> all_verticies;
    std::vector<GLuint> all_indicies;
    std::vector<GLfloat> all_normals;

    unsigned int offset=0;
    for(int i=0;i<all_geometry.size();i++)//For each geometry mesh in our list created above.
    {
        //Add the verticies coordinates from each geometry mesh to one vector.
        all_verticies.insert(all_verticies.end(),all_geometry[i]->mVerticies.begin(),all_geometry[i]->mVerticies.end());
        //Add the normals coordinates from each geometry mesh to one vector
        all_normals.insert(all_normals.end(),all_geometry[i]->mNormals.begin(),all_geometry[i]->mNormals.end());

        //Combine the triangle indicies in to one vector.
        for(int x=0;x<all_geometry[i]->mIndicies.size();x++)
        {
            all_indicies.push_back(all_geometry[i]->mIndicies[x]+offset);//remember to offset the indicies
        }
        offset=(unsigned int)all_verticies.size()/3;//calculate the offset.
    }


    mNumIndicies=all_indicies.size();//total number of triangles


    //*** Send the data to opengl section  ****
    //Create the vertex buffer
    glGenBuffers(1, &mVertexBufferHandle);
    //Bind the vertex buffer to be an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferHandle);
    //Copy our vertex data to the opengl buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*all_verticies.size(), all_verticies.data(), GL_STATIC_DRAW);

    //Create the index buffer
    glGenBuffers(1, &mIndexBufferHandle);
    //Bind the index buffer to be an element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferHandle);
    //Copy our index data to the opengl buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * all_indicies.size(), all_indicies.data(), GL_STATIC_DRAW);

    //Create the normal buffer
    glGenBuffers(1, &mNormalBufferHandle);
    //Bind the normal buffer to be an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferHandle);
    //Copy our normal data to the opengl buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*all_normals.size(), all_normals.data(), GL_STATIC_DRAW);



    //***  Set up the View Matricies and Lights Section  ****
    //Find the largest coordinate in our vertex data.
    //We are using this information to set the position of our camera and light outside the geometry
    std::vector<GLfloat>::iterator iter=std::max_element(all_verticies.begin(),all_verticies.end());
    mMaxCoord=*iter;

    //Create the view matrix
    mViewMatrix.setToIdentity();
    mViewMatrix.lookAt( QVector3D(mMaxCoord*2,0,0), // Camera is at (mMaxCoord*2,0,0), in World Space
                        QVector3D(0,0,0), // and looks at the origin
                        QVector3D(0,0,1)  // Head is up (set to 0,-1,0 to look upside-down)
                        );

    //Create the light
    mLightPos=QVector3D(mMaxCoord*2,mMaxCoord*2,mMaxCoord*2);
    //Transform the light by the view matrix
    mLightPos=mViewMatrix*mLightPos;

    //Send some of our data to opengl.  This data is constant and doesn't change with each render
    glUseProgram(mProgramHandle);
    glUniform3f(mLightPositionUHandle, mLightPos[0], mLightPos[1], mLightPos[2]);
    glUniform3f(mColorUHandle, 1.0, 0.0, 0.0);

}

void OpenGLExample::paintGL(void)
{
    //This function is run each time a render is needed.
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //***   Create Projection matrix section ****
    mProjectionMatrix.setToIdentity();
    mProjectionMatrix.perspective(60.0,(float)(width()/(float)height()),(float) 0.01,(float)(mMaxCoord*4));

    // Our ModelViewProjection : multiplication of our 3 matrices.  The mRotate matrix is used to rotate the geometry
    //So it is acting light an additional model transform.
    mMVP = mProjectionMatrix*mViewMatrix* mRotate; // Remember, matrix multiplication is the other way around
    mMV=mViewMatrix*mRotate;

    // Use our shader
    glUseProgram(mProgramHandle);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(mMVPMatrixUHandle, 1, GL_FALSE, mMVP.data());
    glUniformMatrix4fv(mMVMatrixUHandle, 1, GL_FALSE, mMV.data());

    //***  Data Array Definitions  ****
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    //Bind the vertex buffer as an array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferHandle);
    //Tell opengl how to read our vertex data.  This will be put in the a_Position in our shader
    glVertexAttribPointer(
                mPositionAHandle,  // The attribute we want to configure
                3,                            // size
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*)0                      // array buffer offset
                );

    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    //Bind the normal buffer as an array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferHandle);
    //Tell opengl how to read our normal data.  This will be put in the a_Normal in our shader
    glVertexAttribPointer(
                mNormalAHandle,  // The attribute we want to configure
                3,                            // size
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*)0                      // array buffer offset
                );


    //Draw the geometry
    glDrawElements(GL_TRIANGLES, mNumIndicies, GL_UNSIGNED_INT,nullptr);

    //Disable the arrays.
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void OpenGLExample::timerEvent(QTimerEvent*)
{
    mTimerCount++;
    if(mTimerCount==70)//We don't want to change our rotation axis every time the timer goes off so we do it every 70 times.
    {
        //Set up the random number generator
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(0, 1);
        do
        {
            //Set a random rotation axis
            mRotateAxis.setX(std::round(dist(e2)));
            mRotateAxis.setY(std::round(dist(e2)));
            mRotateAxis.setZ(std::round(dist(e2)));
        }
        while (mRotateAxis.x()==0 &&mRotateAxis.y()==0 && mRotateAxis.z()==0);//Keep running until we have a non zero axis
        mTimerCount=0;
    }

    //Rotate the geometry by 4 degrees.
    mRotate.rotate(4,mRotateAxis);

   update();  //Update graphics.  This will call paintGL
}

void OpenGLExample::resizeGL(int w, int h)
{
    mWidth = w;
    mHeight = h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

}

void OpenGLExample::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Escape:  /*  Escape Key */
        exit(0);
        break;
    default:
        break;
    }
    e->accept();  // Don't pass any key events to parent
}





