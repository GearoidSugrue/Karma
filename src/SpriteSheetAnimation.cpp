#include "SpriteSheetAnimation.h"

SpriteSheetAnimation::SpriteSheetAnimation()
{
    //ctor
    frameCounter = 0;
    switchFrame = 8; //change later??
}

SpriteSheetAnimation::~SpriteSheetAnimation()
{
    //dtor
}

void SpriteSheetAnimation::Update(Animation &ani)
{
    if(ani.IsActive())
    {
        frameCounter++;
        if(frameCounter >= switchFrame)
        {
            frameCounter = 0;
            ani.CurrentFrame().first++;
            if(ani.CurrentFrame().first * ani.GetFrameDimensions().first >= al_get_bitmap_width(ani.Image()))
            {
                ani.CurrentFrame().first = 0;
            }
        }

    }
    else
    {
        frameCounter = 0;
        ani.CurrentFrame().first = 0;
    }

    ani.SourceRect() = al_create_sub_bitmap(ani.Image(), ani.CurrentFrame().first * ani.GetFrameDimensions().first,
                            ani.CurrentFrame().second * ani.GetFrameDimensions().second, ani.GetFrameDimensions().first,
                            ani.GetFrameDimensions().second);
}
