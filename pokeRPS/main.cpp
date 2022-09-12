#include "RPS.h"

#include "Text.h"
#include "Image.h"
#include "Button.h"
#include "UIManager.h"

unsigned WINDOWWIDTH, WINDOWHEIGHT;
float ratioW = 1.0f, ratioH = 1.0f;

float prevTime = 0.0f, currTime, deltaTime;
bool lastClicked = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	ratioW *= (float)width / (float)WINDOWWIDTH;
	ratioH *= (float)height / (float)WINDOWHEIGHT;

	WINDOWWIDTH = width;
	WINDOWHEIGHT = height;

	Yui::updateAll();

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || Yui::toClose)
		glfwSetWindowShouldClose(window, true);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	for (UIElement* element : Yui::UIElements)
	{
		Button* bp = dynamic_cast<Button*>(element);
		if (bp && bp->isHovering((float)mouseX, (float)mouseY))
		{
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				if (!Yui::cutScene && !lastClicked)
				{
					lastClicked = true;
					bp->func();
					break;
				}
			}
			else
				lastClicked = false;
		}
	}
}

int main()
{
	/*
		Setting up OpenGL (GLFW, GLAD)
	*/
	if (!glfwInit())
	{
#ifdef _DEBUG
		std::cout << "failed to initialize glfw" << std::endl;
#endif
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int monitorX, monitorY;
	glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	WINDOWWIDTH = (unsigned)(videoMode->height * 0.825f); WINDOWHEIGHT = (unsigned)(videoMode->height * 0.825f);

#ifdef _DEBUG
	std::cout << "window resolution: " << WINDOWWIDTH << "x" << WINDOWHEIGHT << std::endl;
#endif

	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "PokeRPS", nullptr, nullptr);
	if (!window)
	{
#ifdef _DEBUG
		std::cout << "failed to initialize window" << std::endl;
#endif
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1); // vsync on
	glfwSetWindowSizeLimits(window, (int)(0.2f * WINDOWHEIGHT), (int)(0.2f * WINDOWHEIGHT), GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSetWindowPos(window, monitorX + (videoMode->width - WINDOWWIDTH) / 2, monitorY + (videoMode->height - WINDOWHEIGHT) / 2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
#ifdef _DEBUG
		std::cout << "failed to initialize glad" << std::endl;
#endif
		return -1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	{
		GLFWimage image;
		image.pixels = stbi_load("images/icon.png", &image.width, &image.height, 0, 4);
		glfwSetWindowIcon(window, 1, &image);
		stbi_image_free(image.pixels);
	}

	/*
		Setting up UI elements
	*/
	stbi_set_flip_vertically_on_load(true);

	RPS::seed();

	UIElement::WINDOWWIDTH = &WINDOWWIDTH;
	UIElement::WINDOWHEIGHT = &WINDOWHEIGHT;

	Text::init("fonts/pokefont.ttf",  &ratioW, &ratioH, 32);
	Image::init();
	Button::init();

	Yui::initSound();
	Yui::UIElements.reserve(10);
	Yui::loadScene(0);
	
	while (!glfwWindowShouldClose(window))
	{
		// timestep update
		currTime = (float)glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		// background
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		// scene based animation
		switch (Yui::scene)
		{
		case 0: // intro menu
			if (((ScrollText*)Yui::UIElements[2])->updateQueue.size() == 0 && ((ScrollText*)Yui::UIElements[2])->elapsed() > 2.1f)
			{
				Yui::UIElements[3]->visible = true;
				Yui::UIElements[4]->visible = true;
			}

			break;

		case 1: // tutorial

			if (((ScrollText*)Yui::UIElements[4])->updateQueue.size() == 0 && ((ScrollText*)Yui::UIElements[4])->elapsed() > 1.2f)
				Yui::UIElements[5]->visible = true;

			break;

		case 2: // maim menu
		{
			Image* squirtle = (Image*)Yui::UIElements[0];
			Image* bulbasaur = (Image*)Yui::UIElements[1];
			Image* charmander = (Image*)Yui::UIElements[2];

			if (squirtle->centerY + squirtle->translation[1] < 1.15f)
				squirtle->applyTranslation(0.115f * deltaTime, 0.115f * deltaTime);
			else
				squirtle->translation = glm::vec3(0.0f, 0.0f, 0.0f);

			if (bulbasaur->centerX + bulbasaur->translation[0] < 1.15f)
				bulbasaur->applyTranslation(0.1f * deltaTime, -0.0175f * deltaTime);
			else
				bulbasaur->translation = glm::vec3(0.0f, 0.0f, 0.0f);

			if (charmander->centerY + charmander->translation[1] > -0.15f)
				charmander->applyTranslation(-0.025f * deltaTime, -0.1f * deltaTime);
			else
				charmander->translation = glm::vec3(0.0f, 0.0f, 0.0f);

			break;
		}

		case 3: // battle
		{
			ScrollText* txt = ((ScrollText*)Yui::UIElements[3]);

			if (txt->phase == 0)
			{
				((Image*)Yui::UIElements[0])->applyTranslation(-0.255f * deltaTime, 0.0f);
				((Image*)Yui::UIElements[1])->applyTranslation(0.255f * deltaTime, 0.0f);
			}
			else if (txt->phase == 1)
			{
				if (txt->elapsed() > 2.4f)
				{
					Yui::UIElements[4]->visible = true;
					Yui::UIElements[5]->visible = true;
					Yui::UIElements[6]->visible = true;

					if (((Button*)Yui::UIElements[4])->hovering && ((Image*)Yui::UIElements[0])->imgPath != "images/charmanderBack.png")
						((Image*)Yui::UIElements[0])->changeTexture("images/charmanderBack.png", true);
					else if (((Button*)Yui::UIElements[5])->hovering && ((Image*)Yui::UIElements[0])->imgPath != "images/squiretleBack.png")
						((Image*)Yui::UIElements[0])->changeTexture("images/squirtleBack.png", true);
					else if (((Button*)Yui::UIElements[6])->hovering && ((Image*)Yui::UIElements[0])->imgPath != "images/bulbasaurBack.png")
						((Image*)Yui::UIElements[0])->changeTexture("images/bulbasaurBack.png", true);
				}
			}
			else if (txt->phase == 3 && txt->elapsed() > 4.33f)
				Yui::loadScene(2);

			break;
		}

		default:
#ifdef _DEBUG
			std::cout << "unknown scene" << std::endl;
#endif
			break;
		}

		Yui::renderAll();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*
		Cleanup
	*/
	Yui::purgeElements();

	Yui::soundEngine->stopAllSounds();
	Yui::soundEngine->drop();

	Text::cleanup();
	Image::cleanup();
	Button::cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();
}