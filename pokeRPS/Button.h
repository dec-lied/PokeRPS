#pragma once

#include <irrKlang/irrKlang.h>

#include "Shader.h"

#include "Text.h"
#include "UIElement.h"

enum ButtonType
{
	BLANK, BLANK_BORDER, TEXT, TEXT_BORDER
};

class Button : public UIElement
{
private:
	// internal
	GLuint VAO, VBO;
	ButtonType buttonType;

	// text based button members
	float lMargin, rMargin, uMargin, dMargin;

	// border button members
	float borderWidth;
	glm::vec4 borderColor;

public:
	// static members & methods
	static std::unique_ptr<Shader> buttonShader;
	static void init();
	static void cleanup();

	// text based button members
	Text* text = nullptr;

	// universal members
	void(*func)();
	bool hovering = false;
	bool clickable = true;
	glm::vec4 bgColor, hoverColor;

	Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	Button(Text* text, float lMargin, float rMargin, float uMargin, float dMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(Text* text, float lMargin, float rMargin, float uMargin, float dMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	~Button();

	// universal methods
	// based on mouse coordinates, returns whether mouse is hovering over this instance
	bool isHovering(float mouseX, float mouseY);

	// inherited
	void update();
	void render();
};

