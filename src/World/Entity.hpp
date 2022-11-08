#include <SFML/System/Vector2.hpp>
#ifndef SOURCE_WORLD_ENTITY_HPP_
#define SOURCE_WORLD_ENTITY_HPP_

class Entity
{
public:
    Entity();
    Entity(int p_id, sf::Vector2f pos);
    void SetPosition(sf::Vector2f position);
    void SetVelocity(sf::Vector2f velocity);
    int GetId();
    int GetType();
    int GetHeading();
    int GetState();
    int GetAnimFrame();
    int GetSpeed();
    sf::Vector2f GetPosition();
    sf::Vector2f GetVelocity();
    void Update(float tick_time);

protected:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    float speed_;
    int id_;
    int type_;
    int heading_;
    int state_;
    int anim_frame_;
};

#endif // SOURCE_WORLD_ENTITY_HPP_