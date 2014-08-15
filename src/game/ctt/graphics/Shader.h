//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Shader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <SDL_opengl.h>

class ShaderProgram;
class Shader
{
protected:
	GLuint m_shaderId;
public:
	Shader(const char *source);
	virtual ~Shader();

	friend class ShaderProgram;
};