#include "FadeAnimation.h"

FadeAnimation::FadeAnimation()
{
    //ctor
}

FadeAnimation::~FadeAnimation()
{
    //dtor
}

void FadeAnimation::LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2])
{
    Animation::LoadContent(image, text, position);
    fadeSpeed = 3.0f;
    increaseFade = false;

}


void FadeAnimation::UnloadContent()
{
    Animation::UnloadContent();
    fadeSpeed = NULL;

}

void FadeAnimation::Update(InputManager input)
{
    if(isActive)
    {
        if(!increaseFade)
        {
            alpha -= fadeSpeed;
            //std::cout<<alpha<<"fading out..."<<std::endl;
        }
        else
        {
            alpha += fadeSpeed;
            //std::cout<<alpha<<fading in..."<<std::endl;
        }

        if(alpha <= 0)
        {
            alpha = 0;
            increaseFade = true;
        }
        else if(alpha >= 255)
        {
            alpha = 255;
            increaseFade = false;
        }
    }
    else
    {
        alpha = 255;
    }

}

void FadeAnimation::SetAlpha(int val)
{
    alpha = val;
    if(alpha == 0)
    {
        increaseFade = true;
    }
    else if(alpha == 255)
    {
        increaseFade = false;
    }

}
