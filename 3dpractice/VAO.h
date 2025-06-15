#ifndef VAO_h
#define VAO_h

#include <glad/glad.h>
#include "VBO.h"

class VAO{
    public:
        unsigned int ID;
        VAO();
        void LinkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void UnBind();
        void Delete();        
};

#endif