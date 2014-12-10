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

/*
        void LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2]);
        void UnloadContent();
        void Update(InputManager input);
        void SetAlpha(int val);
*/
    protected:

    private:
    float fadeSpeed;
    bool increaseFade;


};

#endif // FADEANIMATION_H
