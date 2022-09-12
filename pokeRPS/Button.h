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
	Text* text = nullptr;
	float xMargin, yMargin;

	// border button members
	float borderWidth;
	glm::vec4 borderColor;

public:
	// static members & methods
	static glm::mat4 projection;
	static std::unique_ptr<Shader> buttonShader;
	static void init();
	static void cleanup();

	// universal members
	void(*func)();
	bool hovering = false;
	bool clickable = true;
	glm::vec4 bgColor, hoverColor;

	Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	~Button();

	// universal methods
	// based on mouse coordinates, returns whether mouse is hovering over this instance
	bool isHovering(float mouseX, float mouseY);

	// inherited
	void update();
	void render();
};

