//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UIButton.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "UIButton.h"

#include <math/Rect.h>
#include <graphics/renderer/UIRenderContext.h>

#include <resources/materials/MaterialLib.h>

namespace UI
{
	Button::Button(const DynString& name, Vector2 position, Vector2 size)
		: Control(name, position, size), m_text(L"Button"), m_font(0), m_material(0), m_geometry(0)
	{
		m_material = MaterialLib::get()->findByName("uiMaterial");
		if (m_material)
			m_material->acquire();

		m_font = new Font("fonts/Tahoma.ttf", 15);

		m_geometry = new Geometry<Vertex2d>();

		Vertex2d vertices[4] = {
			{ m_position.x, m_position.y, 0, 1, 0xFF000000 },
			{ m_position.x, m_position.y + m_size.y, 0, 0, 0xFF000000 },
			{ m_position.x + m_size.x, m_position.y + m_size.y, 1, 0, 0xFF000000 },
			{ m_position.x + m_size.x, m_position.y, 1, 1, 0xFF000000 }
		};

		uint16 indices[6] = {
			0, 1, 2,
			0, 2, 3
		};

		m_geometry->fillData(vertices, 4, indices, 2);
	}

	Button::~Button()
	{
		if (m_material)
			m_material->release();

		if (m_font)
		{
			delete m_font;
			m_font = 0;
		}

		if (m_geometry)
		{
			delete m_geometry;
			m_geometry = 0;
		}
	}

	void Button::setText(const WDynString& text)
	{
		m_text = text;
	}

	WDynString Button::getText()
	{
		return m_text;
	}

	void Button::render(UIRenderContext& context)
	{			
		Renderer::get().setMaterial(m_material);
		Renderer::get().renderGeometry(m_geometry);

		m_font->render(m_text, Rect(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y), Color(1,1,1,1), Font::DrawFlags::HorizontalCenter | Font::DrawFlags::VerticalCenter);
	}
};