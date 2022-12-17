#ifndef PONG_GAME_H
#define PONG_GAME_H
#include "Vector.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  sf::Text menu_text;
  sf::Text game_text;
  sf::Text red_score_text;
  sf::Text blu_score_text;
  sf::Text quit_text;
  sf::Text end_text;
  sf::Text quit_options;
  sf::Text menu_options;
  sf::Font font;

 private:
  void spawn();
  std::string winner = "Saxton Hale";
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Sprite paddle_red;
  sf::Sprite paddle_blu;
  sf::Texture ball_texture;
  sf::Texture redpad_texture;
  sf::Texture bluepad_texture;
  float speed = 450;
  float paddle_speed = 30;
  GameState menu;
  bool YN;
  Vector ball_direction;
  float paddle_red_accel = 0;
  float paddle_blu_accel = 0;
  int red_score = 0;
  int blu_score = 0;
};

#endif // PONG_GAME_H