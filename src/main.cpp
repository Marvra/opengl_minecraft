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
#include"Chunk.h"

#define window_width 800
#define window_height 800


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

	Chunk chunk;
	chunk.generateChunk();

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(chunk.vertices, chunk.vertices.size() * sizeof(float));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(chunk.indices, chunk.indices.size() * sizeof(int));

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

	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CCW);

	// variables needed to calculate FPS
	// double currTime, prevTime, timeDiff = 0.0f;
	// unsigned int counter = 0;

	// variables to get drawing a frame 
	double currFrameDraw, prevFrameDraw = 0.0f; 


	Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 3.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		currFrameDraw =  glfwGetTime();
		// FPS calculation 
		// currTime = glfwGetTime();
		// timeDiff = currTime - prevTime;
		// counter++;
	
		// if (timeDiff >= (1.0/30.0))
		// {
		// 	std::cout << "\033[H\033[J"; // clears window idk black magic 
		// 	std::cout << "Vertices count: " << chunk.vertices.size() << std::endl;
		// 	std::cout << "Indices count: " << chunk.indices.size() << std::endl;
		// 	std::cout <<  "FPS : " <<  counter/timeDiff << std::endl;
		// 	prevTime = currTime;
		// 	counter = 0;
		// }

		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		wall.Bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, chunk.indices.size(), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

		std::cout << "Frame draw: " << (currFrameDraw - prevFrameDraw) * 1000 << " ms" << std::endl;

		prevFrameDraw = currFrameDraw;
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