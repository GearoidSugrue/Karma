#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include <Animation.h>
#include<iostream>

class FadeAnimation : public Animation
{
    public:
        FadeAnimation();
        virtual ~FadeAnimation();

        void SetIncrease(bool val);
        void Update(Animation &ani);
    protected:

    private:
    float fadeSpeed;
    bool increaseFade;
};

#endif // FADEANIMATION_H
