//-------------------------------------------------------
// Filename: FragmentShader.frag
//
// Description:  A simple fragment shader for the opengl shape example
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------
#version 120

varying vec3 v_Color;          // This is the color from the vertex shader interpolated across the
                               // triangle per fragment.

// The entry point for our fragment shader.
void main()
{
    gl_FragColor = vec4(v_Color,1.0);    // Pass the color directly through the pipeline.
}
