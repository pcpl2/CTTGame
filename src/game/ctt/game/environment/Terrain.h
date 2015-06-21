//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Terrain.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <graphics/Geometry.h>

#include <btBulletDynamicsCommon.h>

class TerrainNode
{
private:
	Geometry<Vertex3d> m_geometry;
	Texture *m_texture;
	Material *m_material;

	Matrix4x4 m_world;

	// Next nodes in projected onto 2d plane
	TerrainNode *m_right;
	TerrainNode *m_left;
	TerrainNode *m_top;
	TerrainNode *m_bottom;

	btRigidBody *m_rigidBody;
public:
	TerrainNode(Vector3 position, uint32 size);
	~TerrainNode();

	void render(RenderContext& context);
};

class Terrain
{
private:
	TerrainNode ***m_node;

	uint32 m_wNodes;
	uint32 m_hNodes;
	uint32 m_width;
	uint32 m_height;
public:
	Terrain(uint32 width, uint32 height);
	~Terrain();

	void render(RenderContext& context);
};