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
    //newScreen = screen;
    transition.SetAlpha(0);
    startTransition = true;
    newScreen = screen;
    transition.SetIsActive(true);
}

void ScreenManager::Initialize()
{
    currentScreen = new SplashScreen;
}

void ScreenManager::LoadContent()
{
    currentScreen->LoadContent();
    blackFader = al_load_bitmap("BlackFade.png");
    float pos[2] = { 0, 0};
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
        transition.Draw(display);
    }
}

void ScreenManager::Transition()
{
    transition.Update(currentScreen->GetInput());
    if(transition.GetAlpha() >= 255) //higher value == faded out ie black image loads
    {
        transition.SetAlpha(255);
        currentScreen->UnloadContent();
        delete currentScreen;
        currentScreen = newScreen;
        currentScreen->LoadContent();
        al_rest(1.0) ;
    }
    else if(transition.GetAlpha() <= 0)
    {
        startTransition = false;
        transition.SetIsActive(false);
    }

}
