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
  if (!redpad_texture.loadFromFile("Data/Images/paddleRed.png"))
  {
    std::cout << "Error loading red paddle texture";
    return false;
  }
  if (!bluepad_texture.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "Error loading blue paddle texture";
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

  paddle_blu.setTexture(bluepad_texture);
  paddle_red.setTexture(redpad_texture);
  ball.setTexture(ball_texture);
  spawn();

  ball_direction.x = 5;
  ball_direction.y = 4;
  ball_direction.normalise();

  return true;
}

void Game::update(float dt)
{
  game_text.setString("("+std::to_string(ball_direction.x)+" "+std::to_string(ball_direction.y)+")");

  ball.move(ball_direction.x * speed * dt, ball_direction.y * speed * dt);

  paddle_red.move(0, paddle_red_accel * paddle_speed * dt);
  paddle_blu.move(0, paddle_blu_accel * paddle_speed * dt);
    // collision check for top and bottom wall
  if (ball.getPosition().y < 0 || (ball.getPosition().y > (window.getSize().y - ball.getGlobalBounds().height)))
  {
    ball_direction.y = ball_direction.y * -1;
  } // collision check for left and right wall
  if (ball.getPosition().x < 0 || (ball.getPosition().x > (window.getSize().x - ball.getGlobalBounds().width)))
  {
    ball_direction.x = ball_direction.x * -1;
  } // collision check for red paddle
  if (ball.getPosition().x < paddle_red.getPosition().x
      && ball.getPosition().y < (paddle_red.getPosition().y + paddle_red.getGlobalBounds().height)
      && ball.getPosition().y > (paddle_red.getPosition().y))
  {
    ball_direction.x = ball_direction.x * -1;
  } // collision check for blue paddle
  if (ball.getPosition().x > (paddle_blu.getPosition().x + paddle_blu.getGlobalBounds().width)
      && ball.getPosition().y < (paddle_blu.getPosition().y + paddle_blu.getGlobalBounds().height)
      && ball.getPosition().y > (paddle_blu.getPosition().y))
  {
    ball_direction.x = ball_direction.x * -1;
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
    window.draw(paddle_red);
    window.draw(paddle_blu);
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
  if (event.key.code == sf::Keyboard::Up)
  {
    paddle_red_accel = -10;
    paddle_blu_accel = -10;
  }
  if (event.key.code == sf::Keyboard::Down)
  {
    paddle_red_accel = 10;
    paddle_blu_accel = 10;
  }
}

void Game::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Up)
  {
    paddle_red_accel = 0;
    paddle_blu_accel = 0;
  }
  if (event.key.code == sf::Keyboard::Down)
  {
    paddle_red_accel = 0;
    paddle_blu_accel = 0;
  }
}

void Game::spawn()
{
  ball.setScale(0.35,0.35);
  ball.setPosition(window.getSize().x / 2 - ball.getGlobalBounds().width / 2,
                   window.getSize().y / 2 - ball.getGlobalBounds().height / 2);

  paddle_red.setPosition(40, window.getSize().y / 2);
  paddle_red.setRotation(90);

  paddle_blu.setPosition(window.getSize().x - 40, window.getSize().y / 2);
  paddle_blu.setRotation(-90);
}