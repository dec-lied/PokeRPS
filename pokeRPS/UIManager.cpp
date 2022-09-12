#include "UIManager.h"

std::vector<UIElement*> Yui::UIElements;
irrklang::ISoundEngine* Yui::soundEngine = irrklang::createIrrKlangDevice();
irrklang::ISound* Yui::bgm;
irrklang::ISoundSource* Yui::openSource;
irrklang::ISoundSource* Yui::cerulSource;
irrklang::ISoundSource* Yui::battleSource; 

unsigned Yui::scene;

bool Yui::toClose = false;
bool Yui::cutScene = false;

void Yui::initSound()
{
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
	for (int i = UIElements.size() - 1; i >= 0; i--)
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
			new ScrollText("Hello there!", 0.325f, 0.6f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, { {3.0f, "Welcome to PokeRPS"}, {3.0f, "Do you know how the"} }),
			new ScrollText("", 0.0825f, 0.5f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, { {8.0f, "pokemon types work?"} }),
			new Button
			(
				new Text("Yes", 0.25f, .14375f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.95f,
				2.75f,
				0.05f,
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
				2.75f,
				0.05f,
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
			new ScrollText("Take a look at this diagram.", 0.49f, 0.47f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, {}),
			new ScrollText("", 0.11f, 0.35f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, { {2.9f, "When you understand it,"} }),
			new ScrollText("", 0.11f, 0.275f, 1.1f, 1.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, { {5.3f, "press play."} }),
			new Button
			(
				new Text("Play", 0.5f, .075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f,
				1.75f,
				0.05f,
				glm::vec4(0.97f, 0.97f, 0.97f, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				[]()
				{
					Yui::soundEngine->play2D("audio/pokeAbutton.mp3");
					Yui::loadScene(3);
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

		Yui::bgm = Yui::soundEngine->play2D(Yui::cerulSource, true);

		Yui::addElements
		(
			7,
			new Image("images/squirtleFront.png", true, -1.8f, -1.25f, 0.3f, 0.3f),
			new Image("images/bulbasaurFront.png", true, -0.775f, 0.85f, 0.3f, 0.3f),
			new Image("images/charmanderFront.png", true, 1.0f, 1.5f, 0.3f, 0.3f),
			new ScrollText("PokeRPS", 0.5f, 0.95f, 2.0f, 2.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, { {3.0f, "PokeRPS"} }),
			new Button
			(
				new Text("Play", 0.5f, 0.65f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				1.5f,
				0.05f,
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
				new Text("Tutorial", 0.5f, 0.375f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.65f,
				1.5f,
				0.05f,
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
				new Text("Quit", 0.5f, 0.1f, 1.5f, 1.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				1.5f,
				0.05f,
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
			new Image("images/questionMarks.png", true, 1.1f, 0.5925f, 0.30f, 0.30f), // own
			new Image("images/questionMarks.png", true, -0.1f, 0.9f, 0.325f, 0.325f), // opponent
			new Image("images/textbox.png", true, 0.5f, 0.3f, 0.975f, 0.3f),
			new ScrollText("Your opponent challenged you!", 0.4575f, 0.375f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 13.0f, { {3.4f, "Which type will you choose?"} }),
			new Button
			(
				new Text("Fire", 0.18f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.75f,
				2.25f,
				0.05f,
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
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's not very effective. Tie!" });
					}
					else if (RPS::opponentType == 1)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "They selected Squirtle." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You lost!" });
					}
					else
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You selected Charmander." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You won!" });
					}

					Yui::cutScene = true;
				}
			),
			new Button
			(
				new Text("Water", 0.50f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.75f,
				2.25f,
				0.05f,
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
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You won!" });
					}
					else if (RPS::opponentType == 1)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You both selected Squirtle." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's not very effective. Tie!" });
					}
					else
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "They selected Bulbasaur." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You lost!" });
					}

					Yui::cutScene = true;
				}
			),
			new Button
			(
				new Text("Grass", 0.82f, 0.075f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				0.75f,
				2.25f,
				0.05f,
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
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You lost!" });
					}
					else if (RPS::opponentType == 1)
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/squirtleFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You selected Bulbasaur." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's super effective. You win!" });
					}
					else
					{
						((Image*)Yui::UIElements[1])->changeTexture("images/bulbasaurFront.png", true);
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 0.0f, "You both selected Bulbasaur." });
						((ScrollText*)Yui::UIElements[3])->updateQueue.push_back({ 2.3f, "It's not very effective. Tie!" });
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

	default:
		Yui::loadScene(0);
		break;
	}
}