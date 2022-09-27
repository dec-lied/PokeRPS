#pragma once

#include "Image.h"

class Sprite : public Image
{
public:
    // universal members
    glm::vec2 translation;
    float scaleX, scaleY;

    Sprite(std::string imgPath, bool alpha, float centerX, float centerY, float width, float height, float scaleX, float scaleY);
    ~Sprite();

    // universal methods
    void setTranslation(glm::vec2 translation);
    void appendTranslation(glm::vec2 translation);

    // inherited
    void update();
    void render();
};