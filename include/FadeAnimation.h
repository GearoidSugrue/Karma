#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include <Animation.h>


class FadeAnimation : public Animation
{
    public:
        FadeAnimation();
        virtual ~FadeAnimation();

        void LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2]);
        void UnloadContent();
        void Update(InputManager input);
        void SetAlpha(int val);

    protected:

    private:
    float fadeSpeed;
    bool increaseFade;


};

#endif // FADEANIMATION_H
