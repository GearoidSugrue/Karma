#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2])
{
    this->image = image;
    this->text = text;
    this->position[0] = position[0];
    this->position[1] = position[1];

    alpha = 255;
    font = al_load_font("slkscr.ttf", 22, NULL);
    sourceRect = image ;
    isActive = false ;
}

void Animation::UnloadContent()
{
    //al_destroy_bitmap(image);
    //al_destroy_bitmap(sourceRect);
    al_destroy_font(font);
    alpha = NULL;
    position[0] = position[1] = NULL;
}

void Animation::Update(InputManager input)
{

}

void Animation::Draw(ALLEGRO_DISPLAY *display)
{
    if(sourceRect != NULL)
    {
        al_draw_tinted_bitmap(sourceRect, al_map_rgba(0, 0, 0, alpha), position[0], position[1], NULL);

    }
    else if(image != NULL) //may never be called if sourecRect == image
    {
        al_draw_tinted_bitmap(image, al_map_rgba(0, 0, 0, alpha), position[0], position[1], NULL);

    }

    if(text != "")
    {
        al_draw_text(font, al_map_rgba(255, 0, 0, alpha), position[0], position[1], NULL, text.c_str());
    }

}

void Animation::SetAlpha(float alpha)
{
    this->alpha = alpha;
}

float Animation::GetAlpha()
{
    return alpha;
}

void Animation::SetIsActive(bool val)
{
    isActive = val;
}

bool Animation::GetIsActive()
{
    return isActive;
}
