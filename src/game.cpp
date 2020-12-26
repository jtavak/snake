#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include "snakelist.h"
#include "loadshaders.h"
#include "vertices.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int dir = 1;

int main(void){

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Snake", NULL, NULL);
	if (!window){
		glfwTerminate();
		return -1;
	}

	glfwSetWindowPos(window, 100, 0);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	if(glewInit() != GLEW_OK)
		return -1;

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	string filepath = "../res/shaders/Basic.shader";
	ShaderSource source = read_shader(filepath);

	unsigned int shader = create_shader(source.vertexShader, source.fragmentShader);
	glUseProgram(shader);

	SnakeList s;
	int squares = 11;
	Vertex v;

	clock_t framestart;
	framestart = clock();
	while (!glfwWindowShouldClose(window)){

		glfwPollEvents();

		if(double(clock()-framestart)/CLOCKS_PER_SEC > 0.075){
			framestart = clock();

			v = calcVertices(s.initialNode, s.foodNode, squares);

			if(dir-s.dir == 1 || dir-s.dir == -3)
				s.turn(1);
			else if(dir-s.dir == -1 || dir-s.dir == 3)
				s.turn(-1);

			s.move(false);

			glClear(GL_COLOR_BUFFER_BIT);

			glBufferData(GL_ARRAY_BUFFER, v.psize, v.positions, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.vsize, v.vertices, GL_STATIC_DRAW);

			glDrawElements(GL_TRIANGLES, squares*6, GL_UNSIGNED_INT, nullptr);
			glfwSwapBuffers(window);

			if(s.game_over() || s.initialNode->x < -1.0 || s.initialNode->x >= 1.0 || s.initialNode->y < -1.1 || s.initialNode->y >= 1.0)
				break;
		}
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    	dir = 0;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    	dir = 2;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    	dir = 3;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    	dir = 1;
}
