#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include<allegro.h>
#include<allegro_image.h>
#include<iostream>
#include<string>
#include "GameScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"
#include "FadeAnimation.h"
#include "GameplayScreen.h"

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
        Animation transition;
        FadeAnimation fadeAni;

        void Transition();
        bool startTransition;

        ALLEGRO_BITMAP *blackFader;
};

#endif // SCREENMANAGER_H
