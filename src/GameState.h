#ifndef PONGSFML_GAMESTATE_H
#define PONGSFML_GAMESTATE_H

class GameState
{
 public:
  enum
  {
    MAIN_MENU = 1,
    PLAY_GAME = 2,
    QUIT_MENU = 3,
    GAME_OVER = 4,
  } State;
};

#endif // PONGSFML_GAMESTATE_H
