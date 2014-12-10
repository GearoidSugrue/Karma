#include "GameScreen.h"

GameScreen::GameScreen()
{
    //ctor
}

GameScreen::~GameScreen()
{
    //dtor
}

void GameScreen::LoadContent()
{


}

void GameScreen::UnloadContent()
{
    //attributes.clear();
    //contents.clear();

}

void GameScreen::Update(ALLEGRO_EVENT ev)
{
    std::cout << "Is this doing anything..." <<std::endl ;

}

void GameScreen::Draw(ALLEGRO_DISPLAY *display)
{

}

InputManager GameScreen::GetInput()
{
    return input;
}
