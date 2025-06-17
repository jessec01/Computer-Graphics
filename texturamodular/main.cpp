#include <glad/glad.h>
#include <GLFW/glfw3.h>

//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include <iostream>
#include <stb/stb_image.h>
#include "shader_s.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "texture.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Vertices coordinates
GLfloat vertices[] =
{
	-1.0f,-1.0f ,0.0f,   1.0f,0.0f,0.0f, 0.0f,0.0f,// Lower left corner
	-1.0f,1.0f , 0.0f,   0.0f,1.0f,0.0f, 0.0f,1.0f,// Lower rightcorner
	1.0f,1.0f ,  0.0f,   0.0f,0.0f,1.0f, 1.0f,1.0f,// Upper corner
	1.0f,-1.0f , 0.0f,   1.0f,1.0f,1.0f, 1.0f,0.0f// Inner left
	
};

GLfloat vertices2[] =
{
	-0.4f,-0.8f ,0.0f,   1.0f,0.0f,0.0f, 0.0f,0.0f,// Lower left corner
	-0.4f,0.0f , 0.0f,   0.0f,1.0f,0.0f, 0.0f,1.0f,// Lower rightcorner
	0.2f,0.0f ,  0.0f,   0.0f,0.0f,1.0f, 1.0f,1.0f,// Upper corner
	0.2f,-0.8f , 0.0f,   1.0f,1.0f,1.0f, 1.0f,0.0f// Inner left
	
};
// Indices for vertices order
GLuint indices2[] =
{
	0, 2, 1, // uper triangulo
    0,3,2    //lower triangulo
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // uper triangulo
    0,3,2    //lower triangulo
};



int main()
{   
	// Enable blending
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	//glViewport(0, 0, 800, 800);
    
    // Enable blending
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("prueba.vs", "prueba.fs");
    
    

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO VAOP;
	VAOP.Bind();
    VBO VBOP(vertices2,sizeof(vertices2));
    EBO EBOP(indices2, sizeof(indices2));

	// Links VBO to VAO
	// Links VBO attributes such as coordinates and colors to VAO
	VAOP.LinkVBO(VBOP, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAOP.LinkVBO(VBOP, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAOP.LinkVBO(VBOP, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOP.UnBind();
	VBOP.UnBind();
	EBOP.UnBind();
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable( GL_BLEND );
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkVBO(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkVBO(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();
    //textura normal 
	// load and create a texture 
	// Texture
	Texture fondo("../texture/fondo.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
	Texture person("../texture/miku.png", GL_TEXTURE_2D, GL_TEXTURE0,GL_RGBA,GL_UNSIGNED_BYTE);
	fondo.texUnit(shaderProgram,"texture2",1);
	person.texUnit(shaderProgram,"texture1",0);
	// Gets ID of uniform called "scale"
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	// Texture
	//Texture popCat("../texture/fondo.jpg", GL_TEXTURE_2D, GL_TEXTURE0, ///GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	/*Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);*/

	//sf::Music music("../⭐Miku Miku Beam!! ⭐ - 람다람 RAMDARAM.mp3"); // Throws sf::Exception if an error occurs

// OR

    
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{

		processInput(window);
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Active();
		//glBindTexture(GL_TEXTURE_2D, texture1);
		//glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		//popCat.Bind();
		fondo.Bind();
		
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		person.Bind();
		VAOP.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	//popCat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}