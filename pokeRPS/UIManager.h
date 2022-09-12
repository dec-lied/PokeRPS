#pragma once

#include <vector>
#include <cstdarg>

#include "RPS.h"
#include "Shader.h"

#include "Text.h"
#include "Image.h"
#include "Button.h"
#include "ScrollText.h"

class Yui
{
public:
	// CORE - UIElements vector
	static std::vector<UIElement*> UIElements;

	static void addElement(UIElement* element);
	static void addElements(unsigned count, ...);
	static void removeElement(UIElement* element);
	static void purgeElements();

	// sound
	static irrklang::ISoundEngine* soundEngine;
	static irrklang::ISoundSource* openSource;
	static irrklang::ISoundSource* cerulSource;
	static irrklang::ISoundSource* battleSource;
	static irrklang::ISound* bgm;

	static void initSound();

	// animation-related members
	static bool toClose;
	static bool cutScene;
	static unsigned scene;

	static void loadScene(unsigned sceneID);

	// QoL calling update and render derived methods 
	static void updateAll();
	static void renderAll();
};
