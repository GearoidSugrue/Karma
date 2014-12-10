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

        void LoadContent(ALLEGRO_BITMAP *image, std::string text, float position[2]);
        void UnloadContent();
        virtual void Update(Animation &ani);
        void Draw(ALLEGRO_DISPLAY *display);//May be virtual...
        //void SetAlpha(float value);//delete

        float &GetSetAlpha();
        bool &IsActive();

//std::pair<int, int> &Animation::NumberOfFrames()

        std::pair<int, int> &NumberOfFrames();
        std::pair<int, int> &CurrentFrame();
        std::pair<int, int> GetFrameDimensions();

        ALLEGRO_BITMAP*& Image();//sprite???
        ALLEGRO_BITMAP*& SourceRect();//sprite???
        //void SetIsActive(bool val);//delete

    protected:


    private:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *image, *sourceRect;
        std::string text;
        float position[2];
        float alpha;
        bool isActive;

        std::pair<int, int> numberOfFrames;
        std::pair<int, int> currentFrame;

};

#endif // ANIMATION_H
