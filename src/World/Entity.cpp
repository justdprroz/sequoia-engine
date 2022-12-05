#include "World/Entity.hpp"

Entity::Entity()
{
    id_ = 0;
    type_ = 0;
    position_ = {0.0f, 0.0f};
    velocity_ = {0.0f, 0.0f};
    speed_ = 5;
    heading_ = 0;
    state_ = 0;
}

Entity::Entity(int p_id, sf::Vector2f pos) : Entity()
{
    id_ = p_id;
    position_ = pos;
}

int Entity::GetId()
{
    return id_;
}

int Entity::GetType()
{
    return type_;
}

int Entity::GetHeading()
{
    return heading_;
}

int Entity::GetState()
{
    return state_;
}

int Entity::GetAnimFrame()
{
    return anim_frame_;
}

int Entity::GetSpeed()
{
    return speed_;
}

void Entity::SetPosition(sf::Vector2f position)
{
    position_ = position;
}

sf::Vector2f Entity::GetPosition()
{
    return position_;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
    velocity_ = velocity;
}

sf::Vector2f Entity::GetVelocity()
{
    return velocity_;
}

void Entity::Update(float tick_time)
{
    position_ += velocity_ * tick_time;
}