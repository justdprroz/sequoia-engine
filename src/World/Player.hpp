#ifndef SOURCE_WORLD_PLAYER_HPP_
#define SOURCE_WORLD_PLAYER_HPP_

#include <World/Entity.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

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

#endif // SOURCE_WORLD_PLAYER_HPP_