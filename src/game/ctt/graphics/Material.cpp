//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Material.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <resources/CacheableResource.h>
#include <core/Logger.h>
#include "Material.h"
#include "Texture.h"

#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

Material::Material(const DynString& name, const FilePath& file)
	: CacheableResource(file),
	  m_name(name),
	  m_program(0),
	  m_hasVertexShader(0),
	  m_hasFragmentShader(0),
	  m_isLoaded(0),
	  m_parameters(Parameters::DEFAULT)
{
}

Material::~Material()
{
	for (TextureData* texture : m_textures)
		delete texture;
	m_textures.clear();
}

void Material::destroy()
{
	for (TextureData* texture : m_textures)
	{
		if (texture->m_texture)
		{
			texture->m_texture->release();
			delete texture->m_texture;
			texture->m_texture = 0;
		}
	}	

	if (m_program)
	{
		delete m_program;
		m_program = 0;
	}

	m_isLoaded = false;
}

bool Material::load()
{
	if (!m_isLoaded)
	{
		// TODO: TextureLib
		for (TextureData* texture : m_textures)
		{
			texture->m_texture = new Texture(FilePath("textures/%s", texture->m_path.get()), texture->m_mipmaps ? true : false);
			texture->m_texture->acquire(); // Acquire texture into material - we are calling free when material is being removed
		}

		m_program = new ShaderProgram();

		if (m_hasVertexShader)
		{
			m_program->attachShader(new VertexShader(FilePath("shaders/%s.vert", m_vertexShaderName.get())));
		}

		if (m_hasFragmentShader)
		{
			m_program->attachShader(new FragmentShader(FilePath("shaders/%s.frag",m_fragmentShaderName.get())));
		}

		m_program->link();
		m_isLoaded = true;
		return true;
	}
	return false;
}

void Material::addTexture(const DynString& name, const FilePath& path, bool mipmaps, TextureWrap wrap[2])
{
	TextureData* data = new TextureData;
	data->m_name = name;
	data->m_path = path;
	data->m_mipmaps = mipmaps ? 1 : 0;
	for (uint32 i = 0; i < 2; ++i)
		data->m_wrap[i] = wrap[i];
	m_textures.pushBack(data);
}


Texture* Material::getTexture(uint32 i)
{
	if (i > m_textures.size())
		return 0;

	Texture * tex = 0;
	uint32 c = i;
	for (TextureData * data : m_textures)
	{
		if (c == 0)
		{
			tex = data->m_texture;
			break;
		}
		c--;
	}
	return tex;
}

Texture* Material::getTexture(const DynString& name)
{
	for (TextureData * data : m_textures)
	{
		if (data->m_name == name)
		{
			return data->m_texture;
		}
	}
	return 0;
}