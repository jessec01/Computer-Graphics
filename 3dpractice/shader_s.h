#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std:: string get_file_contents(const char* filname);
class Shader{
    public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    void Active();
    void Delete();
    void setInt(const std::string &name, int value)const ;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    
};
#endif