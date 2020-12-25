#include <iostream>
using namespace std;

struct ShaderSource{
	string vertexShader;
	string fragmentShader;
};

ShaderSource read_shader(string &filepath);
unsigned int create_shader(const string &vertexShader, const string &fragmentShader);
