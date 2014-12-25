#include "ScreenManager.h"


ScreenManager &ScreenManager::GetInstance()
{
    static ScreenManager instance;
    return instance;
}

ScreenManager::ScreenManager()
{
    //ctor
}

ScreenManager::~ScreenManager()
{
    //dtor
}

void ScreenManager::AddScreen(GameScreen *screen)
{
    transition.GetSetAlpha() = 0;
    fadeAni.SetIncrease(true);
    startTransition = true;
    newScreen = screen;
    transition.IsActive() = true;
}

void ScreenManager::Initialize()
{
    currentScreen = new SplashScreen;
}

void ScreenManager::LoadContent()
{
    currentScreen->LoadContent();
    blackFader = al_load_bitmap("BlackFade.png");
    std::pair<float, float> pos = std::pair<float, float>(0, 0);
    transition.LoadContent(blackFader, "", pos);
    startTransition = false;
}

void ScreenManager::UnloadContent()
{
    al_destroy_bitmap(blackFader);
    transition.UnloadContent();
}

void ScreenManager::Update(ALLEGRO_EVENT ev)
{
    if(!startTransition)
    {
        currentScreen->Update(ev);
    }
    else
    {
        Transition();
    }
}

void ScreenManager::Draw(ALLEGRO_DISPLAY *display)
{
    currentScreen->Draw(display);
    if(startTransition)
    {
        if(currentScreen->cameraPosition.first != NULL)
        {
            transition.position.first = currentScreen->cameraPosition.first;
        }
        transition.Draw(display);
    }
    al_flip_display(); //Flips everything on the back buffer onto the disply. Only have this once!!!!
}

void ScreenManager::Transition()
{
    fadeAni.Update(transition);
    if(transition.GetSetAlpha() >= 255)
    {
        transition.position.first = 0;
        transition.GetSetAlpha() = 255;
        currentScreen->UnloadContent();
        delete currentScreen;
        currentScreen = newScreen;
        currentScreen->LoadContent();
    }
    else if(transition.GetSetAlpha() <= 0)
    {

        startTransition = false;
        transition.IsActive() = false;
    }
}
