#include "GameplayScreen.h"

GameplayScreen::GameplayScreen()
{
    //ctor
}

GameplayScreen::~GameplayScreen()
{
    //dtor
}

void GameplayScreen::LoadContent()
{
    player.LoadContent();


}

void GameplayScreen::UnloadContent()
{
    player.UnloadContent();

}

void GameplayScreen::Update(ALLEGRO_EVENT ev)
{
    player.Update(ev);//, input);

}

void GameplayScreen::Draw(ALLEGRO_DISPLAY *display)
{
    player.Draw(display);

}
