#pragma once

#include <string>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Texture.h"

#include "UIElement.h"

class Image : public UIElement
{
private:
	// internal
	GLuint VAO, VBO;
	Texture texture;

public:
	// static members & methods
	static glm::mat4 projection;
	static std::unique_ptr<Shader> imageShader;
	static void init();
	static void cleanup();

	// universal members
	std::string imgPath;
	glm::mat4 viewMatrix;
	glm::vec3 translation;

	Image(std::string imgPath, bool alpha, float centerX, float centerY, float width, float height);
	~Image();

	// universal methods
	// given image file path and alpha, changes texture
	void changeTexture(std::string imgPath, bool alpha);

	// given change in x and y, translates image
	void applyTranslation(float deltaX, float deltaY);

	// inherited
	void update();
	void render();
};

