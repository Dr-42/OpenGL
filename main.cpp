#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#define PI 3.14159265358979323846
#include "shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//vertices of a rectangle 0.5 units wide and 0.5 units tall
double vertices[] = {
	1.0, 1.0, 0.0,
	1.0, -1.0, 0.0,
	-1.0, -1.0, 0.0,
	-1.0, 1.0, 0.0
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

float dx = 0.5;
float dy = 0;
float d_scale = 2;

bool key_pressed = false;

float scale = 0.01;

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(720, 720, "OpenGL", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader;
	shader.load("shad.vert", "shad.frag");

	// Do buffer stuff
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)){
		processInput(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		shader.SetUniform("dx", dx);
		shader.SetUniform("dy", dy);
		shader.SetUniform("d_scale", d_scale);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){
		if(!key_pressed){
			key_pressed = true;
			scale *= 2;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){
		if(!key_pressed){
			key_pressed = true;
			scale /= 2;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE){
		key_pressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE){
		key_pressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		dy -= scale;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		dy +=  scale;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		dx += scale;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		dx -= scale;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		d_scale -= scale;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		d_scale += scale;
	}

	std::cout<<scale<<std::endl;

}
