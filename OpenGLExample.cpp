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
static int timer_interval = 50;        // timer interval (millisec)

//Constructor
OpenGLExample::OpenGLExample( QWidget *parent ) : QOpenGLWidget(parent)
{
    startTimer( timer_interval );
    //add dataloaded = bool_value;
    //add dataset = bool_value;
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
    mColorAHandle=0;
    mColorUHandle=0;
    mTimerCount=0;
    mRotateAxis.setX(1);
    mRotateAxis.setY(1);
    data_loaded = false;
    data_set = false;
}

//Destructor
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
    glClearColor(0.0f, 0.6f, 0.0f, 0.0f);


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

//    // Get a handle for our "u_Color" uniform
//    mColorUHandle = glGetUniformLocation(mProgramHandle, "u_Color");


    // Get a handle for our "a_Position" attribute
    mPositionAHandle = glGetAttribLocation(mProgramHandle, "a_Position");

    // Get a handle for our "a_Normal" attribute
    mNormalAHandle = glGetAttribLocation(mProgramHandle, "a_Normal");

    // Get a handle for our "a_Color" attribute
    mColorAHandle = glGetAttribLocation(mProgramHandle, "a_Color");



    //*** Geometry Mesh Generation Section  ***
    //Create the triangle mesh for our basic shapes

    ////This stuff removed and moved to MainWindow.cpp in generate_geometry


    //*** Prepare the geometry mesh to be passed to opengl  ***

    ////This stuff removed and moved to "load_data" at the end of this file




    //***  Set up the View Matricies and Lights Section  ****
    //Find the largest coordinate in our vertex data.
    //We are using this information to set the position of our camera and light outside the geometry
    //std::vector<GLfloat>::iterator iter=std::max_element(mAll_verticies.begin(),mAll_verticies.end());
    mMaxCoord=5;

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


}

void OpenGLExample::paintGL(void)
{
    //This function is run each time a render is needed.
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ////ADDED STUFF FROM INITIALIZE_GL
    if(data_set)
    {
    //*** Send the data to opengl section  ****
    //Create the vertex buffer
    glGenBuffers(1, &mVertexBufferHandle);
    //Bind the vertex buffer to be an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferHandle);
    //Copy our vertex data to the opengl buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mAll_verticies.size(), mAll_verticies.data(), GL_STATIC_DRAW);

    //Create the index buffer
    glGenBuffers(1, &mIndexBufferHandle);
    //Bind the index buffer to be an element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferHandle);
    //Copy our index data to the opengl buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mAll_indicies.size(), mAll_indicies.data(), GL_STATIC_DRAW);

    //Create the normal buffer
    glGenBuffers(1, &mNormalBufferHandle);
    //Bind the normal buffer to be an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferHandle);
    //Copy our normal data to the opengl buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mAll_normals.size(), mAll_normals.data(), GL_STATIC_DRAW);

    //Create the color buffer
    glGenBuffers(1, &mColorBufferHandle);
    //Bind the color buffer to be an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferHandle);
    //Copy our color data to the opengl buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mAll_colors.size(), mAll_colors.data(), GL_STATIC_DRAW);

    data_set = false;
    data_loaded = true;

    }
    ////
    //// END Stuff added from INITIALIZE_GL


    //***   Create Projection matrix section ****
    mProjectionMatrix.setToIdentity();
    mProjectionMatrix.perspective(60.0,(float)(width()/(float)height()),(float) 0.01,(float)(mMaxCoord*4));

    // Our ModelViewProjection : multiplication of our 3 matrices.  The mRotate matrix is used to rotate the geometry
    //So it is acting light an additional model transform.
    mMVP = mProjectionMatrix*mViewMatrix* mRotate; // Remember, matrix multiplication is the other way around
    mMV=mViewMatrix*mRotate;

    // Use our shader
    glUseProgram(mProgramHandle);

    if(data_loaded)
    {

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

    //3rd attribute buffer : colors
    glEnableVertexAttribArray(2);
    //Bind the color buffer as an array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferHandle);
    //Tell opengl how to read our color data.  This will be put in the a_Color in our shader
    glVertexAttribPointer(
                mColorAHandle,  // The attribute we want to configure
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

void OpenGLExample::load_data(std::vector<MeshGeometry3D*> all_geometry)
{
    unsigned int offset=0;
    for(int i=0;i<all_geometry.size();i++)//For each geometry mesh in our list created above.
    {
        //Add the verticies coordinates from each geometry mesh to one vector.
        mAll_verticies.insert(mAll_verticies.end(),all_geometry[i]->mVerticies.begin(),all_geometry[i]->mVerticies.end());
        //Add the normals coordinates from each geometry mesh to one vector
        mAll_normals.insert(mAll_normals.end(),all_geometry[i]->mNormals.begin(),all_geometry[i]->mNormals.end());

        //Add the colors from each geometry mesh to one vector
        for(int j=0;j<all_geometry[i]->mNormals.size()/3; j++)
        {
            mAll_colors.push_back(all_geometry[i]->Color[0]);
            mAll_colors.push_back(all_geometry[i]->Color[1]);
            mAll_colors.push_back(all_geometry[i]->Color[2]);

        }

        //Combine the triangle indicies in to one vector.
        for(int x=0;x<all_geometry[i]->mIndicies.size();x++)
        {
            mAll_indicies.push_back(all_geometry[i]->mIndicies[x]+offset);//remember to offset the indicies
        }
        offset=(unsigned int)mAll_verticies.size()/3;//calculate the offset.
    }


    mNumIndicies=mAll_indicies.size();//total number of triangles

    if(mNumIndicies != 0)
    {
        data_set = true;
        update();
    }
}




