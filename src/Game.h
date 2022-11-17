#ifndef PONG_GAME_H
#define PONG_GAME_H
#include "Vector.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:
  void spawn();
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Sprite paddle_red;
  sf::Sprite paddle_blu;
  sf::Text menu_text;
  sf::Text game_text;
  sf::Text score_text;
  sf::Font font;
  sf::Texture ball_texture;
  sf::Texture redpad_texture;
  sf::Texture bluepad_texture;
  bool in_menu;
  float speed = 500;
  float paddle_speed = 30;
  Vector ball_direction;
  float paddle_red_accel = 0;
  float paddle_blu_accel = 0;
  int red_score = 0;
  int blu_score = 0;
};

#endif // PONG_GAME_H