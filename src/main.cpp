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
#include"World.h"

#define window_width 800
#define window_height 800


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "YoutubeOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

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

	Shader shaderProgram("./res/shaders/default.vert", "./res/shaders/default.frag");

	World world;
	world.generateChunks();

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
	//double currFrameDraw, prevFrameDraw = 0.0f; 


	Camera camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 3.0f));

	while (!glfwWindowShouldClose(window))
	{
	
		//currFrameDraw =  glfwGetTime();
		//FPS calculation 
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

		world.renderChunks();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

		//std::cout << "Frame draw: " << (currFrameDraw - prevFrameDraw) * 1000 << " ms" << std::endl;

		//prevFrameDraw = currFrameDraw;

		//chunk->generateChunk();
	}

	//delete chunk;
	// Delete all the objects we've created
	wall.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}