
#ifndef PONG_GAME_H
#define PONG_GAME_H

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

 private:
  void spawn();
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Text menu_text;
  sf::Font font;
  sf::Texture ball_texture;
  bool in_menu;
  float speed = 200;

};

#endif // PONG_GAME_H
