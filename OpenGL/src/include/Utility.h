#pragma once
#include <GL/glew.h>
#include <iostream>
#include <type_traits>
/* For General */
#define ASSERT(X) if (!(X)) __debugbreak(); // Accept one predicate expression X and break if it is false
#define GLCall(X) GLClearError();\
    X;\
    ASSERT(GLLogCall(#X,__FILE__,__LINE__));\






/* For OpenGL */    
void GLClearError();                                              // Clear all OpenGL errors from the error queue
bool GLLogCall(const char* function, const char* file, int line); // Log OpenGL errors, return true if no error, false if there is an error