#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::LoadContent(ALLEGRO_BITMAP *image, std::string text, std::pair<float, float> pos)//float pos[2])
{
    this->image = image;
    this->text = text;
    //this->position[0] = pos[0];
    //this->position[1] = pos[1];

    position.first = pos.first;
    position.second  = pos.second;
    //position = pos; //Use this instead of ^^^

    //std::pair<float, float> position;

    numberOfFrames = std::pair<int, int>(8, 1);
    currentFrame = std::pair<int, int>(0, 0);

    //GetFrameDimensions = 0;



    alpha = 255;
    font = al_load_font("slkscr.ttf", 22, NULL);
    sourceRect = image ;//delete this???
    isActive = false ;
}

void Animation::UnloadContent()
{
    //al_destroy_bitmap(image); // comment out???d  ...causing it to crash
    //al_destroy_bitmap(sourceRect);
    al_destroy_font(font);
    alpha = 0;
    //position[0] = position[1] = 0;
    position = std::pair<float, float>(0, 0);
    isActive = NULL;
    text = "";
    numberOfFrames = std::pair<int, int>(0, 0);
    currentFrame = std::pair<int, int>(0, 0);
    std::cout<<"destroying an Animation..."<<std::endl;

    //fadeSpeed = NULL;
}

void Animation::Update(Animation &ani)
{


}

void Animation::Draw(ALLEGRO_DISPLAY *display)
{
    if(sourceRect != NULL)
    {
        al_draw_tinted_bitmap(sourceRect, al_map_rgba(255, 255, 255, alpha), position.first, position.second, NULL);

    }
    /*
    else if(image != NULL) //may never be called if sourecRect == image
    {
        al_draw_tinted_bitmap(image, al_map_rgba(0, 0, 0, alpha), position[0], position[1], NULL);

    }
    */

    if(text != "")
    {
        al_draw_text(font, al_map_rgba(255, 0, 0, alpha), position.first, position.second, NULL, text.c_str());
    }

}

/*
void Animation::GetSetAlpha(float alpha)//delete
{
    this->alpha = alpha;
}
*/

float &Animation::GetSetAlpha()
{
    return alpha;
}

/*
void Animation::SetIsActive(bool val)//delete
{
    isActive = val;
}
*/

bool &Animation::IsActive()
{
    return isActive;
}

std::pair<float, float> &Animation::Position()
{
    return position;
}

std::pair<int, int> &Animation::NumberOfFrames()
{
    return numberOfFrames;
}

std::pair<int, int> &Animation::CurrentFrame()
{
    return currentFrame;
}

std::pair<int, int> Animation::GetFrameDimensions()
{
    std::pair<int, int> frameD(al_get_bitmap_width(image) / numberOfFrames.first, al_get_bitmap_height(image) / numberOfFrames.second);
    return frameD;
}

ALLEGRO_BITMAP* &Animation::SourceRect()
{
    return image;
}

ALLEGRO_BITMAP* &Animation::Image()
{
    return sourceRect;
}

