//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/fonts/Font.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/String.h>
#include <core/DynString.h>
#include <core/SharedPtr.h>
#include <core/List.h>

class Font
{
private:	
	struct GlyphData
	{
		uint8 set;
		float x;
		float y;
		float w;
		float h;
		float top;
		float left;
		float bmw;
		float bmh;
		float advanceX;
	};

	uint32 m_textureId;

	Material* m_material;

	bool m_loaded;

	GlyphData m_data[65535];
	uint32 m_size;
public:
	Font(const FilePath& fontPath, uint32 size);
	~Font();

	void render(const WDynString& string, const Rect& rect, const Color& color, flags32 flags, Vector2 scale = Vector2(1,1));

	Font::GlyphData getData(widechar c);

	// NOTE: It does not handle multi-line text!
	float calculateWidth(const WDynString& string);

	// NOTE: It does not handle multi-line text!
	float calculateHeight(const WDynString& string);
public:
	struct DrawFlags
	{
		enum Type
		{
			None = 0, // 0
			NoClip = 1, // 1
			DisableColorCodding = 2, // 10

			// Separated position enum?
			VerticalCenter = 4, // 100
			HorizontalCenter = 8, // 1000
		};
	};

	friend class Renderer;
};