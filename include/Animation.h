#ifndef ANIMATION_H
#define ANIMATION_H

#include<iostream>
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

        void LoadContent(ALLEGRO_BITMAP *image, std::string text, std::pair<float, float> pos);
        void UnloadContent();
        virtual void Update(Animation &ani);
        void Draw(ALLEGRO_DISPLAY *display);

        float &GetSetAlpha();
        bool &IsActive();

        std::pair<int, int> &NumberOfFrames();
        std::pair<int, int> &CurrentFrame();
        std::pair<int, int> GetFrameDimensions();

        std::pair<float, float> &Position();

        ALLEGRO_BITMAP*& Image();
        ALLEGRO_BITMAP*& SourceRect();

        std::pair<float, float> position;
    protected:
    private:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *image, *sourceRect;
        std::string text;
        float alpha;
        bool isActive;

        std::pair<int, int> numberOfFrames;
        std::pair<int, int> currentFrame;
};

#endif // ANIMATION_H
