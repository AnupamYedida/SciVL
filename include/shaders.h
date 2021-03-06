/*------------shaders.h-------------------------------------------------------//
*
* Purpose: this header file holds all the juicy details about shaders
*
*   Notes: This file is heavily influenced by:
*               https://learnopengl.com/#!Getting-started/Shaders
*          generalize shader class for different types of shaders
*
*-----------------------------------------------------------------------------*/

#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>

// Shader struct to hold all the necessary initialization parameters

struct Shader{
    // The program ID
    GLuint Program = 0;

    // Constructor that reads and builds the shader
    void Load(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

    // Function to use the program
    void Use();
};

#endif
