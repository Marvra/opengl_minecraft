#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"stb_image.h"
#include"Texture.h"
#include"Camera.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#define window_width 800
#define window_height 800



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   	TexCoord  //
  //  x	    y      z							  // x	   y	 		 y - up/down //
    -0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
     0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
     0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f,

    -0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
     0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
    -0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
     0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f,

    -0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
    -0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
    -0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f,

     0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
     0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
     0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
     0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f,

    -0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
     0.5f, 0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
    -0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
     0.5f, 0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f,

    -0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
     0.5f,-0.5f, 0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 0.0f,
    -0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 1.0f,
     0.5f,-0.5f,-0.5f,     0.83f, 0.70f, 0.44f,		1.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	// front side
	1, 0, 2,
	1, 2, 3,

	// back side
	4, 5, 6,
	6, 5, 7,

	// left side 
	8, 9, 10,
	10, 9, 11,

	// right side
	13, 12, 14,
	13, 14, 15,

	// top 
	17, 16, 18,
	17, 18, 19,

	// bottom
	20, 21, 22,
	22, 21, 23
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "YoutubeOpenGL", NULL, NULL);
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
	glViewport(0, 0, window_width, window_height);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        std::cerr << "Failed to get primary monitor!" << std::endl;
        glfwTerminate();
        return -1;
    }


	int monitor_width, monitor_height;
	glfwGetMonitorWorkarea(monitor, NULL, NULL, &monitor_width, &monitor_height);

	glfwSetWindowPos(window, monitor_width, (int)((monitor_height-window_height)/2));



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("./res/shaders/default.vert", "./res/shaders/default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	std::string texturePath = "./res/textures/wall.jpg";

	Texture wall(texturePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	wall.texUnit(shaderProgram, "tex0", 0);


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	// variables needed to calculate FPS
	double currTime, prevTime, timeDiff = 0.0f;
	unsigned int counter = 0;

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};


	Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 3.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// FPS calculation 
		currTime = glfwGetTime();
		timeDiff = currTime - prevTime;
		counter++;
	
		if (timeDiff >= (1.0/30.0))
		{
			std::cout << "\033[H\033[J"; // clears window idk black magic 
			std::cout <<  "FPS : " <<  counter/timeDiff << std::endl;
			prevTime = currTime;
			counter = 0;
		}

		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		wall.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		for(int i = 0; i <= 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			if(i % 3 == 0)
			{
				angle = glfwGetTime() * 25.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}

			GLuint model_unifrom =  glGetUniformLocation(shaderProgram.ID, "modelMatrix");
			glUniformMatrix4fv(model_unifrom, 1, GL_FALSE, glm::value_ptr(model));
			// Draw primitives, number of indices, datatype of indices, index of indices
			glDrawElements(GL_TRIANGLES, sizeof(vertices)/sizeof(int), GL_UNSIGNED_INT, 0);
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	wall.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}