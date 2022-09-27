#include "Sprite.h"

Sprite::Sprite(std::string imgPath, bool alpha, float centerX, float centerY, float width, float height, float scaleX, float scaleY)
    : Image(imgPath, alpha, centerX, centerY, width, height)
    , translation(glm::vec2(0.0f))
    , scaleX(scaleX)
    , scaleY(scaleY)
{
	GLfloat vertices[]
	{
		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 1.0f, // tl
		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 0.0f, // bl
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 1.0f, // tr

		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 0.0f, // bl
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 0.0f, // br
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 1.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0x00);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite()
{

}

void Sprite::setTranslation(glm::vec2 translation)
{
    this->translation = translation;

	this->update();
}

void Sprite::appendTranslation(glm::vec2 translation)
{
    this->translation[0] += translation[0];
    this->translation[1] += translation[1];

	this->update();
}

void Sprite::update()
{
	GLfloat vertices[]
	{
		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 1.0f, // tl
		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 0.0f, // bl
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 1.0f, // tr
																																																	    
		(this->centerX - (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		0.0f, 0.0f, // bl
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY - (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 0.0f, // br
		(this->centerX + (((this->width / 2.0f)) * this->scaleX) + this->translation[0]) * *UIElement::WINDOWWIDTH, (this->centerY + (((this->height / 2.0f)) * this->scaleY) + this->translation[1]) * *UIElement::WINDOWHEIGHT,		1.0f, 1.0f  // tr
	};

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void Sprite::render()
{
	if (!this->visible)
		return;

	Image::imageShader->use();
	Image::imageShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(UIElement::projection));

	glBindVertexArray(this->VAO);
	this->texture.bindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}