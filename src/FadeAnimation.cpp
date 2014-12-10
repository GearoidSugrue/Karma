#include "FadeAnimation.h"

FadeAnimation::FadeAnimation()
{
    //ctor
    fadeSpeed = 3.5f;
    increaseFade = false;
}

FadeAnimation::~FadeAnimation()
{
    //dtor
}

/*
void FadeAnimation::LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2])
{
    Animation::LoadContent(image, text, position);
    fadeSpeed = 3.5f;
    increaseFade = false;

}



void FadeAnimation::UnloadContent()
{
    Animation::UnloadContent();
    fadeSpeed = NULL;

}
*/
void FadeAnimation::Update(Animation &ani)
{
    if(ani.IsActive())
    {
        if(!increaseFade)
        {
            ani.GetSetAlpha() -= fadeSpeed;
            //std::cout<<alpha<<"fading out..."<<std::endl;
        }
        else
        {
            ani.GetSetAlpha() += fadeSpeed;
            //std::cout<<alpha<<fading in..."<<std::endl;
        }

        if(ani.GetSetAlpha() <= 0)
        {
            ani.GetSetAlpha() = 0;
            increaseFade = true;
        }
        else if(ani.GetSetAlpha() >= 255)
        {
            ani.GetSetAlpha() = 255;
            increaseFade = false;
        }
    }
    else
    {
        ani.GetSetAlpha() = 255;
    }

}

void FadeAnimation::SetIncrease(bool val)
{
    increaseFade = val;
}

