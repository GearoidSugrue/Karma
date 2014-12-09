#ifndef GAME_H
#define GAME_H


class Game
{

public:
    //Game();
    //virtual ~Game();
    void Start();

protected:

private:
  bool IsExiting();
  void GameLoop();

  enum GameState { Uninitialized, ShowingSplash, Paused,
          ShowingMenu, Playing, Exiting };

  static GameState _gameState;
  //static sf::RenderWindow _mainWindow;
};


#endif // GAME_H
