#include "Game.h"
#include "Vector.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-bold.ttf"))
  {
    std::cout << "Error loading font";
    return false;
  }
  if (!ball_texture.loadFromFile("Data/Images/ball.png"))
  {
    std::cout << "Error loading ball texture";
    return false;
  }
  in_menu = true;
  menu_text.setString("Press enter to start game");
  menu_text.setFont(font);
  menu_text.setCharacterSize(65);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 2 - menu_text.getGlobalBounds().height / 2);

  game_text.setString("("+std::to_string(ball_direction.x)+" "+std::to_string(ball_direction.y)+")");
  game_text.setFont(font);
  game_text.setCharacterSize(20);
  game_text.setFillColor(sf::Color::White);
  game_text.setPosition(20, 20);

  ball.setTexture(ball_texture);
  spawn();

  ball_direction.x = 9;
  ball_direction.y = 26;
  ball_direction.normalise();

  return true;
}

void Game::update(float dt)
{
  game_text.setString("("+std::to_string(ball_direction.x)+" "+std::to_string(ball_direction.y)+")");
  ball.move(ball_direction.x * speed * dt, ball_direction.y * speed * dt);
  if (ball.getPosition().y < 0 || (ball.getPosition().y > (window.getSize().y - ball.getGlobalBounds().height)))
  {
    ball_direction.y = ball_direction.y * -1;
    ball_direction.affector();
    ball_direction.normalise();
  }
  if (ball.getPosition().x < 0 || (ball.getPosition().x > (window.getSize().x - ball.getGlobalBounds().width)))
  {
    ball_direction.x = ball_direction.x * -1;
    ball_direction.affector();
    ball_direction.normalise();
  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_text);
  }
  else if (!in_menu)
  {
    window.draw(ball);
    window.draw(game_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    in_menu = !in_menu;
  }
}

void Game::spawn()
{
  ball.setScale(0.5,0.5);
  ball.setPosition(window.getSize().x / 2 - ball.getGlobalBounds().width / 2,
                   window.getSize().y / 2 - ball.getGlobalBounds().height / 2);
}