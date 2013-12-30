// Defines basic variables and functions that all shaders will need
// Author: Matt Critelli

#pragma once
#ifndef _BASESHADER_H_
#define _BASESHADER_H_

// Includes
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

class BaseShader{
public:
	BaseShader(void);
	BaseShader(const BaseShader&);
	~BaseShader(void);
	bool InitializeShader(std::string, std::string, std::vector<string>);
protected:
	bool checkCompileStatus(std::string, GLuint);
	char* LoadSourceFile(const char*);
public:
	const char* m_fsSource;
	const char* m_vsSource;
	GLuint m_program;
};

#endif