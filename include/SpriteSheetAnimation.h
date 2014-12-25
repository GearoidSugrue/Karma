#ifndef SPRITESHEETANIMATION_H
#define SPRITESHEETANIMATION_H

#include"Animation.h"

class SpriteSheetAnimation : public Animation
{
    public:
        SpriteSheetAnimation();
        virtual ~SpriteSheetAnimation();

        void Update(Animation &ani);

    protected:
    private:
        int frameCounter, switchFrame;
};

#endif // SPRITESHEETANIMATION_H
