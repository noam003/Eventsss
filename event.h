#ifndef EVENT_H
#define EVENT_H

#include <SFML/Graphics.hpp>

struct Event{
    sf::RectangleShape eventBox;
    sf::Text eventName;
    sf::Text eventAddr;
};

#endif //EVENT_H