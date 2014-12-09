#ifndef ANIMATION_H
#define ANIMATION_H


#include<string>
#include<allegro.h>
#include<allegro_image.h>
#include<allegro_font.h>
#include"InputManager.h"


class Animation
{
    public:
        Animation();
        virtual ~Animation();

        virtual void LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2]);
        virtual void UnloadContent();
        virtual void Update(InputManager input);
        void Draw(ALLEGRO_DISPLAY *display);//May be virtual...
        virtual void SetAlpha(float value);
        float GetAlpha();

        void SetIsActive(bool val);
        bool GetIsActive();

    protected:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *image, *sourceRect;
        std::string text;
        float position[2];
        float alpha;
        bool isActive;

    private:


};

#endif // ANIMATION_H
