#ifndef SEQUOIA_ENGINE_SRC_WORLD_PLAYER_
#define SEQUOIA_ENGINE_SRC_WORLD_PLAYER_

#include <string>

#include <SFML/Window/Event.hpp>

#include "World/Entity.hpp"


class Player : public Entity
{
public:
    Player();
    Player(int id, sf::Vector2f pos);
    void HandleEvent(sf::Event &event);
    void Update(float tick_time);

private:
    std::string name_;
    bool pressed_[4] = {false, false, false, false};
};

#endif /* SEQUOIA_ENGINE_SRC_WORLD_PLAYER_ */
