
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

  ball.setTexture(ball_texture);
  spawn();
  return true;
}

void Game::update(float dt)
{
  if (going_up)
  {
    ball.move(0, 1.0f * speed * dt);
  }
  else
  {
    ball.move(0, -1.0f * speed * dt);
  }
  if
    ((ball.getPosition().y > (window.getSize().y - ball.getGlobalBounds().height))
     || (ball.getPosition().y < 0))
  {
    going_up = !going_up;
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

void Vector::normalise()
{

}