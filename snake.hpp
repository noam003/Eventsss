// Copyright 2022 Rashid B. Kolaghassi rbrk@bu.edu

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <SFML/Graphics.hpp>

using std::vector;
using std::deque;
using std::string;

class Fruit {
 private:
  sf::RectangleShape apple;
 public:
  Fruit();

  void set_position (sf::Vector2f update_position) {
    //  function to set position of apple
    apple.setPosition(update_position);
  }

  sf::RectangleShape get_fruit () {
    //   function to create fruit for engine class
    return apple;
  }
};

Fruit::Fruit() {
  // class constructor to create apple properties
  apple.setSize(sf::Vector2f(20, 20));
  apple.setFillColor(sf::Color::Red);
  apple.setPosition(400, 200);
}


class Snake_Part {   //   class to create snake parts
 private:
  sf::Vector2f part_position;
  sf::RectangleShape part;
  sf::Vector2f part_size = {20, 20};

 public:
  explicit Snake_Part(sf::Vector2f begin_position);

  sf::Vector2f get_position() {
    return part_position;
  }


  void setPosition(sf::Vector2f new_part_position) {
    part_position = new_part_position;
  }


  sf::RectangleShape get_shape() {
    return part;
  }

  void update_position() {
    part.setPosition(part_position);
  }
};


Snake_Part::Snake_Part(sf::Vector2f begin_position) {
  part.setSize(part_size);
  part.setFillColor(sf::Color::Blue);
  part.setPosition(begin_position);
  part_position = begin_position;
}

class Border {
 private:
  vector <sf::RectangleShape> border_shape;

 public:
  vector <sf::RectangleShape> get_border() {
    //  function to create border segments and place them into a vector
    border_shape.resize(4);

    border_shape.at(0) = sf::RectangleShape(sf::Vector2f(700, 10));
    border_shape.at(0).setPosition(0.f, 0.f);

    border_shape.at(1) = sf::RectangleShape(sf::Vector2f(700, 10));
    border_shape.at(1).setPosition(0.f, 440.f);

    border_shape.at(2) = sf::RectangleShape(sf::Vector2f(10, 430));
    border_shape.at(2).setPosition(0.f, 10.f);

    border_shape.at(3) = sf::RectangleShape(sf::Vector2f(10, 430));
    border_shape.at(3).setPosition(690.f, 10.f);


    for (int i = 0; i < 4; i++)
      border_shape.at(i).setFillColor(sf::Color::White);

    return border_shape;
  }
} ;



class Engine {  //  game engine that deals with game logic, window and graphics generation
 private:
  vector<int> window_res = {700, 450};
  const int FPS = 5;
  sf::RenderWindow window;
  static const sf::Time time_per_frame;

  vector<Snake_Part> snake;
  int head_direction, head_speed, snake_parts_add, pause_state, current_state, score;
  deque <int> head_direction_que;
  bool game_run = false;
  bool instruct_page = false;

  sf::Time t_since_previous_move;

  Fruit apple;
  Border border;

  vector <sf::RectangleShape> draw_border = border.get_border();

  sf::Font arcade_font;

 public:

  enum Direction {UP, RIGHT, DOWN, LEFT};
  enum State {RUNNING, PAUSED, ENDGAME};

  void homepage () {
    // Create a window
    window.create(sf::VideoMode(window_res.at(0), window_res.at(1)), "Snake Game");
    window.setFramerateLimit(FPS);
  }

  void input_homepage () {
    sf::Event event;
    // closing window
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        // register key inputs

        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        if (event.key.code == sf::Keyboard::Enter) {
          game_run = true;
          run();
        }

        if (event.key.code == sf::Keyboard::I)
          instruct_page = true;

      }
    }
  }


  void draw_homepage () {
    //  function to draw homepage screen
    window.clear(sf::Color::Black);

    arcade_font.loadFromFile("fonts/ARCADECLASSIC.TTF");
    sf::Text home_title;
    home_title.setFont(arcade_font);
    home_title.setFillColor(sf::Color::Green);
    home_title.setCharacterSize(80);
    home_title.setPosition(150, 100);
    home_title.setString("SNAKE GAME");

    sf::Text home_text;
    home_text.setFont(arcade_font);
    home_text.setFillColor(sf::Color::Yellow);
    home_text.setCharacterSize(15);
    home_text.setPosition(230, 250);
    home_text.setString("PRESS  ENTER   TO   BEGIN   GAME");

    sf::Text home_text_2;
    home_text_2.setFont(arcade_font);
    home_text_2.setFillColor(sf::Color::Yellow);
    home_text_2.setCharacterSize(15);
    home_text_2.setPosition(220, 263);
    home_text_2.setString("PRESS  I   TO   VIEW   INSTRUCTIONS");

    sf::Text home_text_3;
    home_text_3.setFont(arcade_font);
    home_text_3.setFillColor(sf::Color::Blue);
    home_text_3.setCharacterSize(30);
    home_text_3.setPosition(167, 60);
    home_text_3.setString("STAY   HOME   TODAY  AND  PLAY");

    window.draw(home_title);
    window.draw(home_text);
    window.draw(home_text_2);
    window.draw(home_text_3);
    window.display();
  }

  void draw_instructions() {
    //  function to draw instructions page
    window.clear(sf::Color::Black);

    arcade_font.loadFromFile("fonts/ARCADECLASSIC.TTF");
    sf::Text home_title;
    home_title.setFont(arcade_font);
    home_title.setFillColor(sf::Color::Yellow);
    home_title.setCharacterSize(50);
    home_title.setPosition(150, 40);
    home_title.setString("INSTRUCTIONS");

    vector <sf::Text> objective, instructions;
    objective.resize(3);
    vector<string> objective_txt, instructions_txt;
    objective_txt.resize(3);
    objective_txt.at(0) = "OBJECTIVE";
    objective_txt.at(1) = "The   objective    of    this    game   is    to    eat    as    many    apples    as    possible";
    objective_txt.at(2) = "As    you    eat    apples     the     snake     grows    longer    and     becomes    faster";


    instructions.resize(3);
    instructions_txt.resize(3);
    instructions_txt.at(0) = "1   Use   up     down     left    right     arrow     keys     to     move     the     snake";
    instructions_txt.at(1) = "2   Press    letter     P     to     pause     game";
    instructions_txt.at(2) = "3   Press    ESCAPE     key     to    quit     game";

    objective = text_instructions(objective, objective_txt, 1);
    instructions = text_instructions(instructions, instructions_txt, 2);



    sf::Text home_text;
    home_text.setFont(arcade_font);
    home_text.setFillColor(sf::Color::Red);
    home_text.setCharacterSize(15);
    home_text.setPosition(230, 320);
    home_text.setString("PRESS  ENTER   TO   BEGIN   GAME");

    window.draw(home_text);

    for (int i = 0; i < 3; i++) {
      window.draw(objective.at(i));
      window.draw(instructions.at(i));
    }
    window.draw(home_title);
    window.display();
  }



  vector <sf::Text> text_instructions(vector<sf::Text> instructions,
                                      vector<string> instructions_txt, int ver) {
    // function to set text strings to specific font, size, color and position

    int y, x = 100;

    if (ver == 1)
      y = 100;

    if(ver == 2)
      y = 160;

    int add = 15;

    for (int i = 0; i < instructions.size(); i++) {
      instructions.at(i).setFont(arcade_font);
      instructions.at(i).setCharacterSize(15);
      instructions.at(i).setFillColor(sf::Color::Yellow);
      instructions.at(i).setPosition(x, y + add * i);
      instructions.at(i).setString(instructions_txt.at(i));

    }

    return instructions;
  }

  void draw_gameover_page() {
    //  function to draw game over page
    window.clear(sf::Color::Black);

    arcade_font.loadFromFile("fonts/ARCADECLASSIC.TTF");
    sf::Text home_title;
    home_title.setFont(arcade_font);
    home_title.setFillColor(sf::Color::Red);
    home_title.setCharacterSize(80);
    home_title.setPosition(150, 100);
    home_title.setString("GAME OVER");

    sf::Text home_text;
    home_text.setFont(arcade_font);
    home_text.setFillColor(sf::Color::Yellow);
    home_text.setCharacterSize(15);
    home_text.setPosition(230, 220);
    home_text.setString("PRESS  ENTER   TO   RESTART   GAME");

    window.draw(home_text);
    window.draw(home_title);
    window.display();
  }

  void intializie() {
    //  function to initalize game
    // build snake
    recreate_snake();
    //set snake speed and direction
    head_speed = 2;
    head_direction = Direction::RIGHT;
    // set time since last move = 0
    t_since_previous_move = sf::Time::Zero;

    snake_parts_add = 0;
    move_fruit();
    score = 0;
  }

  void update_direction(int new_head_direction) {
    //  input direction to direction_que if direction is not repeated
    if (head_direction_que.size() == 0) {
      head_direction_que.push_back(new_head_direction);
    } else {
      if (head_direction_que.back() != new_head_direction)
        head_direction_que.push_back(new_head_direction);
    }
  }

  void input() {
    sf::Event event;
    // closing window
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        // if user inputs arrow key, run update_direction function
        if (event.key.code == sf::Keyboard::Up)
          update_direction(Direction::UP);
        if (event.key.code == sf::Keyboard::Down)
          update_direction(Direction::DOWN);
        if (event.key.code == sf::Keyboard::Right)
          update_direction(Direction::RIGHT);
        if (event.key.code == sf::Keyboard::Left)
          update_direction(Direction::LEFT);

        if (event.key.code == sf::Keyboard::P)
          pause_game();
        if(event.key.code == sf::Keyboard::Enter)
          reset();
      }
    }
  }

  void update () {
    //  function to update snake direction, position, fruit placement,
    //  game-state through checks for
    //  snake-snake collision and snake-border collision
    if (t_since_previous_move.asSeconds() >= sf::seconds(1.f / float(head_speed)).asSeconds()) {
      sf::Vector2f current_pos = snake.at(0).get_position();
      sf::Vector2f last_pos = current_pos;

      if (head_direction_que.size() != 0 ) {

        if (head_direction == Direction::UP)
          if (head_direction_que.front() != Direction::DOWN)
            head_direction = head_direction_que.front();

        if (head_direction == Direction::DOWN)
          if (head_direction_que.front() != Direction::UP)
            head_direction = head_direction_que.front();

        if (head_direction == Direction::RIGHT)
          if (head_direction_que.front() != Direction::LEFT)
            head_direction = head_direction_que.front();

        if (head_direction == Direction::LEFT)
          if (head_direction_que.front() != Direction::RIGHT)
            head_direction = head_direction_que.front();

        head_direction_que.pop_front();
      }

      if (snake_parts_add) {
        update_snake_parts();
        snake_parts_add = snake_parts_add - 1;
      }

      // updating head position:
      sf::Vector2f new_pos;
      if (head_direction == Direction::UP)
        new_pos = {current_pos.x, current_pos.y - 20};
      if (head_direction == Direction::DOWN)
        new_pos = {current_pos.x, current_pos.y + 20};
      if (head_direction == Direction::LEFT)
        new_pos = {current_pos.x - 20, current_pos.y};
      if (head_direction == Direction::RIGHT)
        new_pos = {current_pos.x + 20, current_pos.y};

      snake.at(0).setPosition(new_pos);

      //  updating tail position
      for (int i = 1; i < snake.size(); i++) {
        current_pos = snake.at(i).get_position();
        snake.at(i).setPosition(last_pos);
        last_pos = current_pos;
      }

      for (int i = 0; i < snake.size(); i++)
        snake.at(i).update_position();

      if (snake.at(0).get_shape().getGlobalBounds().intersects(
            apple.get_fruit().getGlobalBounds())) {

        snake_parts_add = snake_parts_add + 4;
        head_speed = head_speed + 1;
        move_fruit();
        score = score + 1;
      }

      //  snake-snake accident
      for (int i = 1; i < snake.size(); i++)
        if (snake.at(0).get_shape().getGlobalBounds()
            .intersects(snake.at(i).get_shape().getGlobalBounds()))
          current_state = State::ENDGAME;

      //  snake-wall accident
      for (int i = 0; i < draw_border.size(); i++)
        if (snake.at(0).get_shape().getGlobalBounds()
            .intersects(draw_border.at(i).getGlobalBounds()))
          current_state = State::ENDGAME;

      t_since_previous_move = sf::Time::Zero;
    } // End update
  }


  void draw () {
    //  function to draw snake apple and score on display
    window.clear(sf::Color::Black);

    arcade_font.loadFromFile("fonts/ARCADECLASSIC.TTF");
    sf::Text score_txt;
    score_txt.setFont(arcade_font);
    score_txt.setFillColor(sf::Color::Red);
    score_txt.setCharacterSize(15);
    score_txt.setPosition(600, 15);

    string score_num = std::to_string(score);
    string score_string = "Score  " + score_num;
    score_txt.setString(score_string);



    for (int i = 0; i < snake.size(); i++)
      window.draw(snake.at(i).get_shape());

    window.draw(apple.get_fruit());

    for (int i = 0; i < 4; i++) {
      window.draw(draw_border.at(i));
    }

    window.draw(score_txt);

    window.display();
  }

  void recreate_snake () {
    // function to create snake at game start/reset
    snake.clear();
    snake.emplace_back(sf::Vector2f(100, 100));
    snake.emplace_back(sf::Vector2f(80, 100));
    snake.emplace_back(sf::Vector2f(60, 100));

  }

  void update_snake_parts () {
    //  function to add snake part to snake_part vector
    sf::Vector2f add_part_position = snake.at(snake.size() - 1).get_position();
    snake.emplace_back(add_part_position);
  }

  void move_fruit () {
    //  function to check randomly generate fruit position in board and check that
    //  new  position is not in snake or in wall
    bool bad_pos = false;
    sf::Vector2f apple_res = sf::Vector2f(
                               window_res.at(0) / 20 - 2, window_res.at(1) / 20 - 2);
    sf::Vector2f updated_apple_pos;
    srand(time(nullptr));
    do {
      bad_pos = false;
      updated_apple_pos.x = (float)(1 + rand() /
                                    ((RAND_MAX + 1u) / (int)apple_res.x)) * 20;
      updated_apple_pos.y = (float)(1 + rand() /
                                    ((RAND_MAX + 1u) / (int)apple_res.y)) * 20;

      for (int i = 0 ; i < snake.size(); i++)
        if (snake.at(i).get_shape().getGlobalBounds().intersects
            (sf::Rect<float>(updated_apple_pos.x,
                             updated_apple_pos.y, 20, 20))) {
          bad_pos = true;
          break;
        }

      for (int j = 0; j < draw_border.size(); j++)
        if (draw_border.at(j).getGlobalBounds().intersects
            (sf::Rect<float>(updated_apple_pos.x,
                             updated_apple_pos.y, 20, 20))) {
          bad_pos = true;
          break;
        }
    } while (bad_pos);
    apple.set_position(updated_apple_pos);
  }

  void reset() {
    //  function to reset game
    //  set snake speed and direction
    head_speed = 2;
    head_direction = Direction::RIGHT;
    //  set time since last move = 0
    t_since_previous_move = sf::Time::Zero;

    head_direction_que.clear();
    snake_parts_add = 0;
    move_fruit();
    recreate_snake();
    current_state = State::RUNNING;
    pause_state = current_state;
    score = 0;
  }

  void pause_game() {
    //  function to keep track of game state if paused
    if (current_state == State::RUNNING) {
      pause_state = current_state;
      current_state = State::PAUSED;
    } else if (current_state == State::PAUSED) {
      current_state = pause_state;
    }
  }

  void run_homepage() {
    if (game_run == false)
      homepage();
    while (window.isOpen()) {
      input_homepage();
      if (instruct_page == false)
        draw_homepage();
      else
        draw_instructions();
    }
  }

  void run() {
    sf::Clock clock;
    intializie();
    while (window.isOpen()) {
      sf::Time del_t = clock.restart();
      if (current_state == State::PAUSED
          || current_state == State::ENDGAME) {
        input();
        if (current_state == State::ENDGAME)
          draw_gameover_page();
        sf::sleep(sf::milliseconds(2));
        continue;
      }
      t_since_previous_move = t_since_previous_move + del_t;
      input();
      update();
      draw();
    }
  }
};
