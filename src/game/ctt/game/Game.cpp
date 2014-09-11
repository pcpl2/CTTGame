//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/Game.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <cstring>

#include "Game.h"

#include <core/Logger.h>
#include <core/SharedPtr.h>
#include <core/Timer.h>

#include <os/OS.h>

#include <graphics/Window.h>
#include <graphics/Model.h>
#include <graphics/Graphics.h>
#include <graphics/renderer/Renderer.h>
#include <graphics/renderer/RenderContext.h>
#include <graphics/Camera.h>
#include <graphics/ImageData.h>

#include <io/CachedItem.h>
#include <io/FileSystem.h>

#include <sound/SoundMgr.h>

#include <game/scene/Scene.h>

#include <graphics/FragmentShader.h>
#include <graphics/VertexShader.h>
#include <graphics/ShaderProgram.h>

#include <game/scene/entities/Entity.h>

#include <resources/ImageLoader.h>
#include <resources/images/bmp/BMPImageLoader.h>

Model * model = 0;
Game::Game()
	: m_isRunning(false), m_isInitialized(false), m_fileSystem(0), m_renderer(0), m_window(0), m_soundMgr(0), m_scene(0)
{
}

Game::~Game()
{
	if (model)
	{
		model->free();
		delete model;
		model = 0;
	}

	if (m_renderer)
	{
		delete m_renderer;
		m_renderer = 0;
	}

	if (m_window)
	{
		delete m_window;
		m_window = 0;
	}

	if (m_soundMgr)
	{
		delete m_soundMgr;
		m_soundMgr = 0;
	}

	if (m_fileSystem)
	{
		delete m_fileSystem;
		m_fileSystem = 0;
	}

	if (m_scene)
	{
		delete m_scene;
		m_scene = 0;
	}
}

bool Game::init()
{
	if (m_isInitialized)
	{
		return false;
	}

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create file system
	m_fileSystem = new FileSystem();
	m_fileSystem->setBaseDirectory(OS::getAppPath());

	// Setup home directory
	char szHomePath[MAX_PATH] = { 0 };
	strcpy(szHomePath, OS::initHomePath("City Transport Tycoon"));

	Logger::init(FilePath("%sgame.log", szHomePath), false);

	// create image loader
	ImageLoader::get()->registerLoader(new BMP::ImageLoader());

	// Create game window
	m_window = new Window();
	m_window->setup("City Transport Tycoon", 800, 600);

	m_renderer = new Renderer();
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	// create game sound mgr
	m_soundMgr = ISoundMgr::create(SoundAPI::OpenAL);

	if (!m_soundMgr->setup())
	{
		Error("game", "Cannot setup SoundMgr!");
		return false;
	}


	/*ISound *sound = m_soundMgr->createSound(SoundType::Effect);

	if (!sound->load("../../data/sounds/test.wav"))
	{
		return false;
	}

	sound->play();*/

	// Create scene
	m_scene = new Scene();

	Entity *entity = new Entity("building");
	
	m_scene->addEntity(entity);

	Camera::current->setPosition(Vector3(4.0f, 2.0f, 0.0f));
	Camera::current->setTarget(Vector3());

	model = new Model("../../data/models/test.mdl");
	model->acquire();

	m_isInitialized = true;
	m_isRunning = true;
	return true;
}

bool Game::pulse()
{
	Timer::frameStart();

	// Main loop - whole magic is done here \o/
	if (m_window)
	{
		if (!m_window->processMessages())
		{
			m_isRunning = false;
		}
	}

	if (m_scene)
		m_scene->updatePhysics();
 
	if (m_renderer)
	{
		m_renderer->preFrame();

		/*if (m_scene)
			m_scene->render();*/
		{
			RenderContext ctx;
			model->render(ctx);			
		}

		m_renderer->postFrame();
	}

	Timer::frameEnd();
	return m_isRunning;
}