#include "Button.h"

std::unique_ptr<Shader> Button::buttonShader = nullptr;

Button::Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: UIElement(x, y, width, height)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
	, borderColor(glm::vec4(0.0f))
	, borderWidth(0.0f)
	, lMargin(0.0f)
	, rMargin(0.0f)
	, uMargin(0.0f)
	, dMargin(0.0f)
{
	this->buttonType = ButtonType::BLANK;

	GLfloat vertices[12]
	{
		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t

		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t


		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT  // t
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)())
	: UIElement(x, y, width, height)
	, borderWidth(borderWidth)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, borderColor(borderColor)
	, func(func)
	, lMargin(0.0f)
	, rMargin(0.0f)
	, uMargin(0.0f)
	, dMargin(0.0f)
{
	this->buttonType = ButtonType::BLANK_BORDER;

	GLfloat vertices[24]
	{
		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t

		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t


		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t



		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t		

		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t				


		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT // t		
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float lMargin, float rMargin, float uMargin, float dMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: UIElement
	(
		text->centerX,
		text->centerY,
		text->width / *UIElement::WINDOWWIDTH,
		text->height / *UIElement::WINDOWHEIGHT
	)
	, text(text)
	, lMargin(lMargin)
	, rMargin(rMargin)
	, uMargin(uMargin)
	, dMargin(dMargin)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
	, borderColor(glm::vec4(0.0f))
	, borderWidth(0.0f)
{
	this->buttonType = ButtonType::TEXT;

	GLfloat vertices[12]
	{
		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t

		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t


		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT  // t
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float lMargin, float rMargin, float uMargin, float dMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)())
	: UIElement
	(
		text->centerX,
		text->centerY,
		text->width / *UIElement::WINDOWWIDTH,
		text->height / *UIElement::WINDOWHEIGHT
	)
	, text(text)
	, lMargin(lMargin)
	, rMargin(rMargin)
	, uMargin(uMargin)
	, dMargin(dMargin)
	, borderWidth(borderWidth)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, borderColor(borderColor)
	, func(func)
{
	this->buttonType = ButtonType::TEXT_BORDER;

	GLfloat vertices[24]
	{
		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t

		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t


		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t



		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t		

		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t				


		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT // t		
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::~Button()
{
	if (this->buttonType == ButtonType::TEXT || this->buttonType == ButtonType::TEXT_BORDER)
		delete this->text;

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Button::init()
{
	Button::buttonShader = std::unique_ptr<Shader>(new Shader("shaders/button.vert", "shaders/button.frag", true));
}

void Button::cleanup()
{
	Button::buttonShader->deleteShader();
}

bool Button::isHovering(float mouseX, float mouseY)
{
	if (!this->visible)
		return false;

	if (mouseX > (((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f) * this->lMargin)))) * *UIElement::WINDOWWIDTH &&
		mouseX < (((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f) * this->rMargin)))) * *UIElement::WINDOWWIDTH &&
		(*UIElement::WINDOWHEIGHT - mouseY) >(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f) * this->dMargin)))) * *UIElement::WINDOWHEIGHT &&
		(*UIElement::WINDOWHEIGHT - mouseY) < (((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f) * this->uMargin)))) * *UIElement::WINDOWHEIGHT)
	{
		this->hovering = true;
		return true;
	}
	else
	{
		this->hovering = false;
		return false;
	}
}


void Button::update()
{
	if (this->text)
	{
		this->text->update();

		this->width = text->width / *UIElement::WINDOWWIDTH;
		this->height = text->height / *UIElement::WINDOWHEIGHT;
	}

	GLfloat vertices[24]
	{
		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t

		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t


		((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) * *UIElement::WINDOWWIDTH, // l
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) * *UIElement::WINDOWHEIGHT, // b

		((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) * *UIElement::WINDOWWIDTH, // r
			((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) * *UIElement::WINDOWHEIGHT, // t



		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t		

		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, // t				


		(((this->centerX - (this->width / 2.0f)) - ((this->width / 2.0f) * this->lMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // l
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY - (this->height / 2.0f)) - ((this->height / 2.0f) * this->dMargin)) - (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT, //  b  		

		(((this->centerX + (this->width / 2.0f)) + ((this->width / 2.0f) * this->rMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWWIDTH, // r
			(((this->centerY + (this->height / 2.0f)) + ((this->height / 2.0f) * this->uMargin)) + (this->borderWidth * ((this->height / 2.0f) + ((this->height / 2.0f))))) * *UIElement::WINDOWHEIGHT // t		
	};

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void Button::render()
{
	if (!this->visible)
		return;

	Button::buttonShader->use();
	Button::buttonShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(UIElement::projection));

	switch (this->buttonType)
	{
	case ButtonType::BLANK:
	case ButtonType::TEXT:
		if (this->hovering)
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
		else
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;

	case ButtonType::BLANK_BORDER:
	case ButtonType::TEXT_BORDER:
		Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->borderColor));
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		if (this->hovering)
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
		else
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;

	default:
#ifdef _DEBUG
		std::cout << "failed to recognize button type" << std::endl;
#endif
		break;
	}

	if (this->text)
		this->text->render();
}
