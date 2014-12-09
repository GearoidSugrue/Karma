//#include "include/Game.h"
#include "Game.h""

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>


//Game::Game()
//{


    //ctor
//}

Game::GameState Game::_gameState = Uninitialized;


void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

    //std::cout <<"this worked";
    _gameState = Game::Playing;

    while(!IsExiting())
    {
    _gameState = Game::Exiting;
    if(!IsExiting())
        GameLoop();
    }
    return ;
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{


}



//Game::~Game()
//{
    //dtor
//}

