#ifndef EBOclass_h
#define EBOclass_h

#include <glad/glad.h>


class EBO{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size);
        void Bind();
        void UnBind();
        void Delete();
};
#endif