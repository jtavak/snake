#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "loadshaders.h"

using namespace std;

ShaderSource read_shader(string &filepath){
	ifstream stream(filepath);
	string line;
	stringstream shaders[2];

	int shaderType = -1;
	while(getline(stream, line)){
		if(line.find("#shader") != string::npos){
			if(line.find("vertex") != string::npos){
				shaderType = 0;
			} 
			else if(line.find("fragment") != string::npos){
				shaderType = 1;
			}
		}
		else{
			shaders[shaderType] << line << "\n";
		}
	}

	struct ShaderSource ss = {shaders[0].str(), shaders[1].str()};
	return ss;
}

unsigned int compile_shader(const string &source, unsigned int type){
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

unsigned int create_shader(const string &vertexShader, const string &fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compile_shader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
