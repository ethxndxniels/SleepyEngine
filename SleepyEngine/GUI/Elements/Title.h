#pragma once
#include "./GUIElement.h"

class Title : public GUIElement
{
public:
	Title( char* title );
	void Draw() override;
};