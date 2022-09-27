#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>
#include <fstream>

class Config
{
private:
	// default members
	const int defaultVolume = 8;
	const float defaultScrollSpeed = 12.0f;
	const glm::vec3 defaultBgColor = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	// universal members
	int volume;
	float scrollSpeed;
	glm::vec3 bgColor;

	Config();
	~Config();

	// universal method
	// writes data to ./settings.config
	void serialize();
	// reads data from ./settings.config and sets methods to it
	void deserialize();

	// sets all members to default
	void reset();
	// sets all members to parameters
	void setAll(unsigned volume, float scrollSpeed, glm::vec3 bgColor);
};

