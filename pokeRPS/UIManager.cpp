#include "UIManager.h"

std::vector<UIElement*> Yui::UIElements;

irrklang::ISound* Yui::bgm;
irrklang::ISoundEngine* Yui::soundEngine = irrklang::createIrrKlangDevice();

irrklang::ISoundSource* Yui::openSource;
irrklang::ISoundSource* Yui::cerulSource;
irrklang::ISoundSource* Yui::battleSource; 

Config Yui::config = Config();

unsigned Yui::scene;

bool Yui::toClose = false;
bool Yui::cutScene = false;

void Yui::initSound()
{
	Yui::soundEngine->setSoundVolume((float)Yui::config.volume / 10.0f);
	Yui::openSource = Yui::soundEngine->addSoundSourceFromFile("audio/pokeopening.mp3");
	Yui::cerulSource = Yui::soundEngine->addSoundSourceFromFile("audio/pokecerulian.mp3");
	Yui::battleSource = Yui::soundEngine->addSoundSourceFromFile("audio/pokebattle.mp3");
}

void Yui::addElement(UIElement* element)
{
	Yui::UIElements.push_back(element);
}

void Yui::addElements(unsigned count, ...)
{
	va_list args;
	va_start(args, count);

	for (unsigned i = 0; i < count; i++)
		Yui::UIElements.push_back(va_arg(args, UIElement*));

	va_end(args);
}

void Yui::removeElement(UIElement* element)
{
	size_t index;
	bool contains = false;

	for (index = 0; index < Yui::UIElements.size(); index++)
	{
		if (Yui::UIElements[index] == element)
		{
			contains = true;
			break;
		}
	}

	if (contains)
		Yui::UIElements.erase(Yui::UIElements.begin() + index);
}

void Yui::purgeElements()
{
	for (int i = (int)UIElements.size() - 1; i >= 0; i--)
	{
		delete Yui::UIElements[i];
		Yui::UIElements.pop_back();
	}
}

void Yui::updateAll()
{
	for (UIElement* element : Yui::UIElements)
		element->update();
}

void Yui::renderAll()
{
	for (UIElement* element : Yui::UIElements)
		element->render();
}

void Yui::loadScene(unsigned sceneID)
{
	Yui::scene = sceneID;
	Yui::purgeElements();

	Yui::cutScene = false;

	switch (sceneID)
	{
	case 0: // intro
	{
		Yui::bgm = Yui::soundEngine->play2D(Yui::openSource, true);

		Yui::addElements
		(
			5,
			new Image("images/textbox.png", true, 0.5f, 0.5f, 0.95f, 0.425f),
			new ScrollText("Hello there!", 0.325f, 0.6f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {1.0f, "Welcome to PokeRPS"}, {1.0f, "Do you know how the"} }),
			new ScrollText("", 0.0825f, 0.5f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {(52.0f - 1.0f) / ScrollText::scrollSpeed + 2.0f, "pokemon types work?"} }),
			new Button
			(
				new Text("Yes", 0.25f, .14375f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.95f,
				1.95f,
				2.75f,
				2.75f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(2);
				}
			),
			new Button
			(
				new Text("No", 0.75f, .14375f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				3.25f,
				3.25f,
				2.75f,
				2.75f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(1);
				}
			)
		);

		Yui::UIElements[3]->visible = false;
		Yui::UIElements[4]->visible = false;

		break;
	}

	case 1: // tutorial
	{
		Yui::addElements
		(
			6,
			new Image("images/typeDiagram.png", true, 0.5f, 0.78f, 0.65f, 0.3735f),
			new Image("images/textbox.png", true, 0.5f, 0.365f, 0.9f, 0.4f),
			new ScrollText("Take a look at this diagram.", 0.49f, 0.47f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), {}),
			new ScrollText("", 0.11f, 0.35f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {30.0f / ScrollText::scrollSpeed, "When you understand it,"} }),
			new ScrollText("", 0.11f, 0.275f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {55.0f / ScrollText::scrollSpeed, "press ready."} }),
			new Button
			(
				new Text("Ready", 0.5f, .075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f,
				2.0f,
				1.75f,
				1.75f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(2);
				}
			)
		);

		Yui::UIElements[5]->visible = false;

		break;
	}

	case 2: // main menu
	{
		Yui::soundEngine->stopAllSoundsOfSoundSource(Yui::openSource);
		Yui::soundEngine->stopAllSoundsOfSoundSource(Yui::battleSource);

		if (!Yui::soundEngine->isCurrentlyPlaying(Yui::cerulSource))
			Yui::bgm = Yui::soundEngine->play2D(Yui::cerulSource, true);

		Yui::addElements
		(
			8,
			new Sprite("images/squirtleFront.png", true, -1.8f, -1.25f, 0.3f, 0.3f, 1.0f, 1.0f),
			new Sprite("images/bulbasaurFront.png", true, -0.775f, 0.85f, 0.3f, 0.3f, 1.0f, 1.0f),
			new Sprite("images/charmanderFront.png", true, 1.0f, 1.5f, 0.3f, 0.3f, 1.0f, 1.0f),
			new ScrollText("PokeRPS", 0.5f, 0.95f, 2.0f, 2.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {3.0f, "PokeRPS"} }),
			new Button
			(
				new Text("Play", 0.5f, 0.7f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				1.75f,
				1.5f,
				1.5f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(3);
				}
			),
			new Button
			(
				new Text("Tutorial", 0.5f, 0.5f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.65f,
				0.65f,
				1.5f,
				1.5f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(1);
				}
			),
			new Button
			(
				new Text("Settings", 0.5f, 0.3f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.65f,
				0.65f,
				1.5f,
				1.5f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(4);
				}
			),
			new Button
			(
				new Text("Quit", 0.5f, 0.1f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				1.75f,
				1.5f,
				1.5f,
				0.15f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::toClose = true;
				}
			)
		);

		((ScrollText*)Yui::UIElements[3])->inf = true;

		break;
	}

	case 3: // battle
	{
		Yui::soundEngine->stopAllSoundsOfSoundSource(Yui::openSource);
		Yui::soundEngine->stopAllSoundsOfSoundSource(Yui::cerulSource);

		Yui::bgm = Yui::soundEngine->play2D(Yui::battleSource, true);

		Yui::addElements
		(
			7,
			new Sprite("images/questionMarks.png", true, 1.1f, 0.5925f, 0.30f, 0.30f, 1.0f, 1.0f), // own
			new Sprite("images/questionMarks.png", true, -0.1f, 0.9f, 0.325f, 0.325f, 1.0f, 1.0f), // opponent
			new Image("images/textbox.png", true, 0.5f, 0.3f, 0.975f, 0.3f),
			new ScrollText("Your opponent challenged you!", 0.4575f, 0.375f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), { {1.17f, "Which type will you choose?"} }),
			new Button
			(
				new Text("Fire", 0.18f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				1.75f,
				2.25f,
				2.25f,
				0.15f,
				glm::vec4(0.973f, 0.565f, 0.188f, 1.0f),
				glm::vec4(1.0f, 0.65f, 0.238f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

					RPS::ownType = 0;
					unsigned winState = RPS::calcWinner();

					if (RPS::opponentType == 0)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/charmanderFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You both selected Charmander." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's not very effective. Tie!" });
					}
					else if (RPS::opponentType == 1)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "They selected Squirtle." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You lost!" });
					}
					else
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You selected Charmander." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You won!" });
					}

					Yui::cutScene = true;
				}
			),
			new Button
			(
				new Text("Water", 0.50f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.75f,
				0.75f,
				2.25f,
				2.25f,
				0.15f,
				glm::vec4(0.408f, 0.596f, 0.969f, 1.0f),
				glm::vec4(0.438f, 0.656f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

					RPS::ownType = 1;
					unsigned winState = RPS::calcWinner();

					if (RPS::opponentType == 0)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/charmanderFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You selected Squirtle." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You won!" });
					}
					else if (RPS::opponentType == 1)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You both selected Squirtle." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's not very effective. Tie!" });
					}
					else
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "They selected Bulbasaur." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You lost!" });
					}

					Yui::cutScene = true;
				}
			),
					new Button
					(
						new Text("Grass", 0.82f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
						0.75f,
						0.75f,
						2.25f,
						2.25f,
						0.15f,
						glm::vec4(0.565f, 0.906f, 0.502f, 1.0f),
						glm::vec4(0.515f, 1.0f, 0.552f, 1.0f),
						glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
						[]()
						{
							Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

							RPS::ownType = 2;
							unsigned winState = RPS::calcWinner();

							if (RPS::opponentType == 0)
							{
								((Image*)Yui::UIElements[1])->changeTexture("images/charmanderFront.png", true);
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "They selected Charmander." });
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You lost!" });
							}
							else if (RPS::opponentType == 1)
							{
								((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You selected Bulbasaur." });
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's super effective. You win!" });
							}
							else
							{
								((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You both selected Bulbasaur." });
								((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 1.3f, "It's not very effective. Tie!" });
							}

							Yui::cutScene = true;
						}
					)
		);

		Yui::UIElements[4]->visible = false;
		Yui::UIElements[5]->visible = false;
		Yui::UIElements[6]->visible = false;

		break;
	}

	case 4: // settings
	{
		Yui::addElements
		(
			20,
			new Text("Settings", 0.5f, 0.95f, 2.0f, 2.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			new Text("Background color", 0.5f, 0.8f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			new Button
			(
				new Text("Pink", 0.14f, 0.7f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.0f, 
				1.0f, 
				1.0f, 
				10.0f, 
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::config.bgColor = glm::vec3(1.0f, 0.82f, 0.863f);
				}
			),
			new Button
			(
				0.14f, 
				0.6f, 
				0.1f, 
				0.1f, 
				0.025f, 
				glm::vec4(1.0f, 0.82f, 0.863f, 1.0f), 
				glm::vec4(1.0f, 0.82f, 0.863f, 1.0f), 
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 
				[]() {}
			),

			new Button
			(
				new Text("Blue", 0.37f, 0.7f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.0f,
				1.0f,
				1.0f,
				10.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::config.bgColor = glm::vec3(0.537f, 0.812f, 0.941f);
				}
			),
			new Button
			(
				0.37f,
				0.6f,
				0.1f,
				0.1f,
				0.025f,
				glm::vec4(0.537f, 0.812f, 0.941f, 1.0f),
				glm::vec4(0.537f, 0.812f, 0.941f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]() {}
			),

			new Button
			(
				new Text("Orange", 0.615f, 0.7f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.2f,
				0.2f,
				1.0f,
				10.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::config.bgColor = glm::vec3(0.98f, 0.784f, 0.596f);
				}
			),
			new Button
			(
				0.615f,
				0.6f,
				0.1f,
				0.1f,
				0.025f,
				glm::vec4(0.98f, 0.784f, 0.596f, 1.0f),
				glm::vec4(0.98f, 0.784f, 0.596f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]() {}
			),

			new Button
			(
				new Text("White", 0.86f, 0.7f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.66f,
				0.66f,
				1.0f,
				10.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::config.bgColor = glm::vec3(1.0f, 1.0f, 1.0f);
				}
			),
			new Button
			(
				0.86f,
				0.6f,
				0.1f,
				0.1f,
				0.025f,
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]() {}
			),

			new Text("Text Scroll Speed:", 0.3f, 0.425f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			new Button
			(
				new Text("<", 0.61f, 0.425f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				3.0f,
				3.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					((Button*)Yui::UIElements[13])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[13])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					if (ScrollText::scrollSpeed > 10.0f)
					{
						Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

						Yui::config.scrollSpeed -= 1.0f;
						ScrollText::scrollSpeed = Yui::config.scrollSpeed;

						((Button*)Yui::UIElements[12])->text->text = std::to_string((unsigned)ScrollText::scrollSpeed);
						((Button*)Yui::UIElements[12])->update();
					}
					else
						Yui::soundEngine->play2D("audio/pokebump.mp3");

					if (ScrollText::scrollSpeed <= 10.0f)
					{
						((Button*)Yui::UIElements[11])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
						((Button*)Yui::UIElements[11])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
					}
				}
			),
			new Button
			(
				new Text(std::to_string((unsigned)ScrollText::scrollSpeed), 0.735f, 0.425f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.0f,
				1.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{

				}
			),
			new Button
			(
				new Text(">", 0.86f, 0.425f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				3.0f,
				3.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					((Button*)Yui::UIElements[11])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[11])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					if (ScrollText::scrollSpeed < 14.0f)
					{
						Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

						Yui::config.scrollSpeed += 1.0f;
						ScrollText::scrollSpeed = Yui::config.scrollSpeed;

						((Button*)Yui::UIElements[12])->text->text = std::to_string((unsigned)ScrollText::scrollSpeed);
						((Button*)Yui::UIElements[12])->update();
					}
					else
						Yui::soundEngine->play2D("audio/pokebump.mp3");

					if (ScrollText::scrollSpeed >= 14.0f)
					{
						((Button*)Yui::UIElements[13])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
						((Button*)Yui::UIElements[13])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
					}
				}
			),

			new Text("Volume:", 0.45f, 0.35f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			new Button
			(
				new Text("<", 0.61f, 0.35f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				3.0f,
				3.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					((Button*)Yui::UIElements[17])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[17])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					if (Yui::config.volume > 0)
					{
						Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

						Yui::config.volume--;
						((Button*)Yui::UIElements[16])->text->text = std::to_string(Yui::config.volume);
						((Button*)Yui::UIElements[16])->update();
					}
					else
						Yui::soundEngine->play2D("audio/pokebump.mp3");

					if (Yui::config.volume <= 0)
					{
						((Button*)Yui::UIElements[15])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
						((Button*)Yui::UIElements[15])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
					}

					Yui::soundEngine->setSoundVolume((float)Yui::config.volume / 10.0f);
				}
			),
			new Button
			(
				new Text(std::to_string(Yui::config.volume), 0.735f, 0.35f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.0f,
				1.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{

				}
			),
			new Button
			(
				new Text(">", 0.86f, 0.35f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				3.0f,
				3.0f,
				1.0f,
				1.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					((Button*)Yui::UIElements[15])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[15])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					if (Yui::config.volume < 10)
					{
						Yui::soundEngine->play2D("audio/pokeAbutton.mp3");

						Yui::config.volume++;
						((Button*)Yui::UIElements[16])->text->text = std::to_string(Yui::config.volume);
						((Button*)Yui::UIElements[16])->update();
					}
					else
						Yui::soundEngine->play2D("audio/pokebump.mp3");

					if (Yui::config.volume >= 10)
					{
						((Button*)Yui::UIElements[17])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
						((Button*)Yui::UIElements[17])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
					}

					Yui::soundEngine->setSoundVolume((float)Yui::config.volume / 10.0f);
				}
			),

			new Button
			(
				new Text("Save and quit", 0.5f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.5f, 
				0.5f, 
				2.0f, 
				2.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::loadScene(2);
				}
			),

			new Button
			(
				new Text("Reset", 0.5f, 0.2f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.25f,
				1.25f,
				2.0f,
				2.0f,
				0.1f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::config.reset();
					ScrollText::scrollSpeed = Yui::config.scrollSpeed;
					Yui::soundEngine->setSoundVolume((float)Yui::config.volume / 10.0f);

					((Button*)Yui::UIElements[11])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[11])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					((Button*)Yui::UIElements[13])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[13])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					((Button*)Yui::UIElements[15])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[15])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					((Button*)Yui::UIElements[17])->bgColor = glm::vec4(0.97f, 0.97f, 0.97f, 1.0f);
					((Button*)Yui::UIElements[17])->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

					((Button*)Yui::UIElements[16])->text->text = std::to_string(Yui::config.volume);
					((Button*)Yui::UIElements[16])->update();

					((Button*)Yui::UIElements[12])->text->text = std::to_string((unsigned)ScrollText::scrollSpeed);
					((Button*)Yui::UIElements[12])->update();
				}
			)
		);

		if (ScrollText::scrollSpeed <= 8)
		{
			((Button*)Yui::UIElements[11])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
			((Button*)Yui::UIElements[11])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
		}

		if (ScrollText::scrollSpeed >= 14)
		{
			((Button*)Yui::UIElements[13])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
			((Button*)Yui::UIElements[13])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
		}

		if (Yui::config.volume <= 0)
		{
			((Button*)Yui::UIElements[15])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
			((Button*)Yui::UIElements[15])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
		}

		if (Yui::config.volume >= 10)
		{
			((Button*)Yui::UIElements[17])->bgColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
			((Button*)Yui::UIElements[17])->hoverColor = glm::vec4(0.663f, 0.663f, 0.663f, 1.0f);
		}

		break;
	}

	default:
		Yui::loadScene(0);
		break;
	}
}