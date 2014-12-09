#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include<iostream>
#include<string>
#include "GameScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"
#include "FadeAnimation.h"

//Allegro Initialise
#include<allegro.h>
#include<allegro_image.h>
//#include<allegro_native_dialog.h>

//#define ScreenHeight 900
//#define Screenwidth 700


class ScreenManager
{
    public:
        static ScreenManager &GetInstance();
        virtual ~ScreenManager();

        void Initialize();
        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev);
        void Draw(ALLEGRO_DISPLAY *display);

        void AddScreen(GameScreen *screen);


    protected:


    private:
        ScreenManager();
        ScreenManager(ScreenManager const&);
        void operator=(ScreenManager const&);

        std::string text;
        GameScreen *currentScreen, *newScreen;
        FadeAnimation transition;

        void Transition();
        bool startTransition;

        ALLEGRO_BITMAP *blackFader;


        //ALLEGRO_FONT *font;

};

#endif // SCREENMANAGER_H
