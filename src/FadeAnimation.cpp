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

void FadeAnimation::Update(Animation &ani)
{
    if(ani.IsActive())
    {
        if(!increaseFade)
        {
            ani.GetSetAlpha() -= fadeSpeed;
        }
        else
        {
            ani.GetSetAlpha() += fadeSpeed;
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
