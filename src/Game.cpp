#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <cmath>

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
  menu.State = menu.MAIN_MENU;

  menu_text.setString("Pong Game\n\nPress Enter to start!");
  menu_text.setFont(font);
  menu_text.setCharacterSize(65);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 2 - menu_text.getGlobalBounds().height / 2);

  game_text.setString("(press 'ctrl' to pause/exit)");
  game_text.setFont(font);
  game_text.setCharacterSize(20);
  game_text.setFillColor(sf::Color(81, 132, 148));
  game_text.setPosition(10, 10);

  red_score_text.setString("Red: "+std::to_string(red_score));
  red_score_text.setFont(font);
  red_score_text.setCharacterSize(40);
  red_score_text.setFillColor(sf::Color::White);
  red_score_text.setPosition(
    200 - (red_score_text.getGlobalBounds().width / 2), 50);

  blu_score_text.setString("Blue: "+std::to_string(blu_score));
  blu_score_text.setFont(font);
  blu_score_text.setCharacterSize(40);
  blu_score_text.setFillColor(sf::Color::White);
  blu_score_text.setPosition(
    (window.getSize().x - 200) -
      (blu_score_text.getGlobalBounds().width / 2), 50);

  quit_text.setString("PAUSED:\nAre you sure you want to quit?");
  quit_text.setFont(font);
  quit_text.setCharacterSize(45);
  quit_text.setFillColor(sf::Color::White);
  quit_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    (window.getSize().y / 2 - menu_text.getGlobalBounds().height / 2) - 150);

  end_text.setFont(font);
  end_text.setCharacterSize(45);
  end_text.setFillColor(sf::Color::White);
  end_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    (window.getSize().y / 2 - menu_text.getGlobalBounds().height / 2) - 150);

  quit_options.setString(">Yes<\nNo");
  quit_options.setFont(font);
  quit_options.setCharacterSize(35);
  quit_options.setFillColor(sf::Color::White);
  quit_options.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    (window.getSize().y / 2 - menu_text.getGlobalBounds().height / 2) + 20);

  paddle_blu.setTexture(bluepad_texture);
  paddle_red.setTexture(redpad_texture);
  ball.setTexture(ball_texture);
  spawn();

  // set ball vector then normalise using Vector class
  ball_direction.x = 5;
  ball_direction.y = 3;
  ball_direction.normalise();

  return true;
}

void Game::update(float dt)
{
  if (red_score == 5)
  {
    menu.State = menu.GAME_OVER;
    winner = "Player 1";
  }
  if (blu_score == 5)
  {
    menu.State = menu.GAME_OVER;
    winner = "Player 2";
  }
  if (menu.State != menu.PLAY_GAME)
  {
    ball.move(0,0);
    paddle_blu.move(0,0);
    paddle_red.move(0,0);
  }
  else if (menu.State == menu.PLAY_GAME)
  {
    blu_score_text.setString("Blue: "+std::to_string(blu_score));
    red_score_text.setString("Red: "+std::to_string(red_score));

    ball.move(ball_direction.x * speed * dt,
              ball_direction.y * speed * dt);
    paddle_red.move(0, paddle_red_accel * paddle_speed * dt);
    paddle_blu.move(0, paddle_blu_accel * paddle_speed * dt);

    // collision check for top and bottom wall
    if (ball.getPosition().y < 0 ||
      (ball.getPosition().y >
       (window.getSize().y - ball.getGlobalBounds().height)))
    {
      ball_direction.y = ball_direction.y * -1;
    } // collision check for left and right wall
    if (ball.getPosition().x < 0)
    {
      blu_score += 1;
      ball.setPosition(window.getSize().x * 0.8, window.getSize().y / 2);
    }
    if (ball.getPosition().x >
        (window.getSize().x - ball.getGlobalBounds().width))
    {
      red_score += 1;
      ball.setPosition(window.getSize().x * 0.2, window.getSize().y / 2);
    }
    // collision check for red paddle
    if (ball.getPosition().x < paddle_red.getPosition().x &&
      ball.getPosition().y <
        (paddle_red.getPosition().y + paddle_red.getGlobalBounds().height) &&
      ball.getPosition().y > (paddle_red.getPosition().y))
    {
      ball_direction.x = ball_direction.x * -1;
    }
    // collision check for blue paddle
    if ((ball.getPosition().x + ball.getGlobalBounds().width) >
        paddle_blu.getPosition().x &&
      ball.getPosition().y >
        (paddle_blu.getPosition().y - paddle_blu.getGlobalBounds().height) &&
      ball.getPosition().y < (paddle_blu.getPosition().y))
    {
      ball_direction.x = ball_direction.x * -1;
    }
    // red paddle check for top and bottom edge of window
    if (paddle_red.getPosition().y >
        (window.getSize().y - paddle_red.getGlobalBounds().height))
    {
      paddle_red.setPosition(
        paddle_red.getPosition().x,
        (window.getSize().y - paddle_red.getGlobalBounds().height));
    }
    if (paddle_red.getPosition().y < 0)
    {
      paddle_red.setPosition(paddle_red.getPosition().x, 0);
    }
    // blue paddle check for top and bottom edge of window
    if (paddle_blu.getPosition().y > window.getSize().y)
    {
      paddle_blu.setPosition(
        paddle_blu.getPosition().x, window.getSize().y);
    }
    if (paddle_blu.getPosition().y < paddle_blu.getGlobalBounds().height)
    {
      paddle_blu.setPosition(
        paddle_blu.getPosition().x, paddle_blu.getGlobalBounds().height);
    }
  }
  if (YN)
  {
    quit_options.setString(">Yes<\nNo");
  }
  else
  {
    quit_options.setString("Yes\n>No<");
  }
}

void Game::render()
{
  // switch statement to switch between the different game states
  // utilises GameState class with an enumerator for different game states
  switch (menu.State)
  {
    case (1):// main menu
    {
      window.draw(menu_text);
      window.draw(menu_options);
      red_score = 0;
      blu_score = 0;
      ball.setPosition(window.getSize().x / 2, window.getSize().y / 2);
      break;
    }
    case (2):// live game
    {
      if (!respawn)
      {
        window.draw(ball);
      }
      window.draw(game_text);
      window.draw(red_score_text);
      window.draw(blu_score_text);
      window.draw(paddle_red);
      window.draw(paddle_blu);
      break;
    }
    case (3):// user-prompted quit
    {
      window.draw(quit_text);
      window.draw(quit_options);
      break;
    }
    case (4):// game-prompted quit
    {
      end_text.setString(
        "Game Over! "+winner+" wins!\nDo you want to play again?");
      window.draw(end_text);
      window.draw(quit_options);
      red_score = 0;
      blu_score = 0;
      ball.setPosition(window.getSize().x / 2, window.getSize().y / 2);
      break;
    }
  }
}

void Game::keyPressed(sf::Event event)
// any references to number key presses are for debugging and testing only
{
  if (event.key.code == sf::Keyboard::Num1)
  {
    menu.State = menu.MAIN_MENU;
  }
  if ((menu.State == menu.MAIN_MENU && event.key.code == sf::Keyboard::Enter) ||
      event.key.code == sf::Keyboard::Num2)
  {
    menu.State = menu.PLAY_GAME;
  }
  if (menu.State == menu.PLAY_GAME)
  {
    if (event.key.code == sf::Keyboard::Up)
    {
      paddle_blu_accel = -10;
    }
    if (event.key.code == sf::Keyboard::Down)
    {
      paddle_blu_accel = 10;
    }
    if (event.key.code == sf::Keyboard::W)
    {
      paddle_red_accel = -10;
    }
    if (event.key.code == sf::Keyboard::S)
    {
      paddle_red_accel = 10;
    }
  }
  // access pause menu whilst only in live game state
  if ((event.key.code == sf::Keyboard::LControl ||
       event.key.code == sf::Keyboard::RControl ||
       event.key.code == sf::Keyboard::Num3) && menu.State == menu.PLAY_GAME)
  {
    menu.State = menu.QUIT_MENU;
  }
  if (event.key.code == sf::Keyboard::Num4)
  {
    menu.State = menu.GAME_OVER;
  }
  if (menu.State == menu.QUIT_MENU || menu.State == menu.GAME_OVER)
  {
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
    {
      YN = !YN;
    }
  }
  if (menu.State == menu.QUIT_MENU)
  {
    if (YN && event.key.code == sf::Keyboard::Enter)
    {
      menu.State = menu.MAIN_MENU;
    }
    else if (!YN && event.key.code == sf::Keyboard::Enter)
    {
      menu.State = menu.PLAY_GAME;
    }
  }
  if (menu.State == menu.GAME_OVER)
  {
    if (YN && event.key.code == sf::Keyboard::Enter)
    {
      menu.State = menu.PLAY_GAME;
    }
    else if (!YN && event.key.code == sf::Keyboard::Enter)
    {
      menu.State = menu.MAIN_MENU;
    }
  }
}

void Game::keyReleased(sf::Event event)
// to prevent jittering of paddle movement and allow for more intuitive control
// when switching direction in quick succession
{
  if (menu.State == menu.PLAY_GAME)
  {
    if (event.key.code == sf::Keyboard::Up && paddle_blu_accel != 10)
    {
      paddle_blu_accel = 0;
    }
    if (event.key.code == sf::Keyboard::Down && paddle_blu_accel != -10)
    {
      paddle_blu_accel = 0;
    }
    if (event.key.code == sf::Keyboard::W && paddle_red_accel != 10)
    {
      paddle_red_accel = 0;
    }
    if (event.key.code == sf::Keyboard::S && paddle_red_accel != -10)
    {
      paddle_red_accel = 0;
    }
  }
}

void Game::spawn()
{
  ball.setScale(0.2,0.2);
  ball.setPosition(
    window.getSize().x / 2 - ball.getGlobalBounds().width / 2,
    window.getSize().y / 2 - ball.getGlobalBounds().height / 2);

  paddle_red.setScale(1.4,1);
  paddle_red.setPosition(40, window.getSize().y / 2);
  paddle_red.setRotation(90);

  paddle_blu.setScale(1.4,1);
  paddle_blu.setPosition(window.getSize().x - 40, window.getSize().y / 2);
  paddle_blu.setRotation(-90);
}

bool Game::respawnTimer(float dt)
{
  respawn_timer_value -= dt * 10;
  std::cout << respawn_timer_value << std::endl;
  if (respawn_timer_value < 0)
  {
    std::cout << "True\n";
    respawn_timer_value = 10;
    return true;
  }
  else
  {
    std::cout << "False\n";
    return false;
  }
}