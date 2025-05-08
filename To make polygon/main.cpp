#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void colorwindows(int index);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLFWwindow* window;
unsigned int vertexShader[3];
unsigned int VBO[3], VAO[3],EBO[2];
unsigned int shaderProgram[3];
unsigned int fragmentShader[3];
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderSource3 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader triangulo
    vertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[0], 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader[0]);
    // check for shader compile errors
    int successt;
    char infoLogt[512];
    glGetShaderiv(vertexShader[0], GL_COMPILE_STATUS, &successt);
    if (!successt)
    {
        glGetShaderInfoLog(vertexShader[0], 512, NULL, infoLogt);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogt << std::endl;
    }
    // vertex shader cuadrado
    vertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[1], 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader[1]);
    // check for shader compile errors
    int successc;
    char infoLogc[512];
    glGetShaderiv(vertexShader[1], GL_COMPILE_STATUS, &successc);
    if (!successc)
    {
        glGetShaderInfoLog(vertexShader[1], 512, NULL, infoLogc);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogc << std::endl;
    }
    // vertex shader pentagono
    vertexShader[2] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[2], 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader[2]);
    // check for shader compile errors
    int successp;
    char infoLogp[512];
    glGetShaderiv(vertexShader[2], GL_COMPILE_STATUS, &successp);
    if (!successp)
    {
        glGetShaderInfoLog(vertexShader[2], 512, NULL, infoLogp);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogp << std::endl;
    }
    // fragment shader triangulo
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader[0]);
    // check for shader compile errors
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &successt);
    if (!successt)
    {
        glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLogt);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogt << std::endl;
    }
    // fragment shader cuadrado
    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader[1]);
    // check for shader compile errors
    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &successc);
    if (!successc)
    {
        glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLogc);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogc << std::endl;
    }
    // fragment shader pentagono
    fragmentShader[2] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[2], 1, &fragmentShaderSource3, NULL);
    glCompileShader(fragmentShader[2]);
    // check for shader compile errors
    glGetShaderiv(fragmentShader[2], GL_COMPILE_STATUS, &successp);
    if (!successp)
    {
        glGetShaderInfoLog(fragmentShader[2], 512, NULL, infoLogp);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogp << std::endl;
    }
    // link shaders triangulo
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader[0]);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    glLinkProgram(shaderProgram[0]);
    // check for linking errors
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &successt);
    if (!successt) {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLogt);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogt << std::endl;
    }
    glDeleteShader(vertexShader[0]);
    glDeleteShader(fragmentShader[0]);
    // link shaders cuadrado
    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader[1]);
    glAttachShader(shaderProgram[1], fragmentShader[1]);
    glLinkProgram(shaderProgram[1]);
    // check for linking errors
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &successc);
    if (!successc) {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLogc);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogc << std::endl;
    }
    glDeleteShader(vertexShader[1]);
    glDeleteShader(fragmentShader[1]);
    // link shaders pentagono
    shaderProgram[2] = glCreateProgram();
    glAttachShader(shaderProgram[2], vertexShader[2]);
    glAttachShader(shaderProgram[2], fragmentShader[2]);
    glLinkProgram(shaderProgram[2]);
    // check for linking errors
    glGetProgramiv(shaderProgram[2], GL_LINK_STATUS, &successp);
    if (!successp) {
        glGetProgramInfoLog(shaderProgram[2], 512, NULL, infoLogp);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogp << std::endl;
    }
    glDeleteShader(vertexShader[2]);
    glDeleteShader(fragmentShader[2]);
    // set up vertex data (and buffer(s)) and configure vertex attributes triangulo
    // ------------------------------------------------------------------
    float verticest[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
    // set up vertex data (and buffer(s)) and configure vertex attributes cuadrado
    // ------------------------------------------------------------------
    float verticesc[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices1[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    // set up vertex data (and buffer(s)) and configure vertex attributes pentagono
    // ------------------------------------------------------------------
    float verticesp[] = {
       0.0f, 0.0f,0.0f,  // Centro del pentágono (V0)
       0.0f, 1.0f,0.0f,  // Vértice superior (V1)
       0.95f, 0.31f,0.0f,  // Vértice superior derecho (V2)
       0.59f, -0.81f,0.0f, // Vértice inferior derecho (V3)
       -0.59f, -0.81f,0.0f, // Vértice inferior izquierdo (V4)
       -0.95f, 0.31f,  0.0f// Vértice superior izquierdo (V5)
    };
    unsigned int indices2[] = {  // note that we start from 0!
        0, 1, 2,  // Triángulo 1
        0, 2, 3,  // Triángulo 2
        0, 3, 4,  // Triángulo 3
        0, 4, 5,  // Triángulo 4
        0, 5, 1   // Triángulo 5
    };
    //config VBA tringulo
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticest), verticest, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    //congig VBA cuadrado
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    glGenBuffers(1, &EBO[0]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesc), verticesc, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    //config VBA Pentagono
    glGenVertexArrays(1, &VAO[2]);
    glGenBuffers(1, &VBO[2]);
    glGenBuffers(1, &EBO[1]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesp), verticesp, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // render loop
    // -----------
    int index=0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        colorwindows(index);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
                if(index<2){
                    index=index+1;
                }
                else {
                    index=0;
                } 
            }
            else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                if (index>0){
                    index=index-1;
                }
                else{
                    index=2;
                }
            }

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        //glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose triangulo
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteProgram(shaderProgram[0]);

    // optional: de-allocate all resources once they've outlived their purpose cuadrado:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO[1]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteBuffers(1, &EBO[0]);
    glDeleteProgram(shaderProgram[1]);

    // optional: de-allocate all resources once they've outlived their purpose pentagono:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO[2]);
    glDeleteBuffers(1, &VBO[2]);
    glDeleteBuffers(1, &EBO[1]);
    glDeleteProgram(shaderProgram[2]);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
void colorwindows(int index){
        if (index==0){
            glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram[0]);
            glBindVertexArray(VAO[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
             // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            //glfwSwapBuffers(window);
            //glfwPollEvents();
        }
        else if (index==1){
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram[1]);
            glBindVertexArray(VAO[1]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0); 
        }
        else if (index==2){
            glClearColor(0.0f, 0.6f, 0.8f, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram[2]);
            glBindVertexArray(VAO[2]);
            glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
            //glBindVertexArray(VAOp); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //GLenum err = glGetError();
            //std::cout << "OpenGL Error: " << err << std::endl;
           // glDrawElements(GL_TRIANGLES, 9,GL_UNSIGNED_INT, 0);
            

        }
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