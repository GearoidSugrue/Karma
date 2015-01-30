#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::LoadContent(ALLEGRO_BITMAP *img, std::string tx, std::pair<float, float> pos)//float pos[2])
{
    image = img;
    text = tx;
    position.first = pos.first;
    position.second  = pos.second;

    numberOfFrames = std::pair<int, int>(8, 1);
    currentFrame = std::pair<int, int>(1, 1);

    alpha = 255;
    font = al_load_font("slkscr.ttf", 22, NULL);
    sourceRect = image ;
    isActive = false ;
}

void Animation::UnloadContent()
{
    al_destroy_font(font);
    alpha = 0;
    position = std::pair<float, float>(0, 0);
    isActive = NULL;
    text = "";
    numberOfFrames = std::pair<int, int>(0, 0);
    currentFrame = std::pair<int, int>(0, 0);
    std::cout<<"destroying an Animation..."<<std::endl;
}

void Animation::Update(Animation &ani)
{
    Update(ani);
}

void Animation::Draw(ALLEGRO_DISPLAY *display)
{
    if(sourceRect != NULL)
    {
        al_draw_tinted_bitmap(sourceRect, al_map_rgba(255, 255, 255, alpha), position.first, position.second, NULL);
    }

    if(text != "")
    {
        al_draw_text(font, al_map_rgba(255, 0, 0, alpha), position.first, position.second, NULL, text.c_str());
    }
}

float &Animation::GetSetAlpha()
{
    return alpha;
}

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
