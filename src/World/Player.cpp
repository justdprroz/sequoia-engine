#include <World/Player.hpp>
Player::Player() : Entity() {
    type_ = 1;
};

Player::Player(int id, sf::Vector2f pos) : Entity(id, pos) {
    type_ = 1;
}

void Player::HandleEvent(sf::Event &event) {
    if (event.KeyPressed) {
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::W){
                pressed_[0] = true;
            }
            if (event.key.code == sf::Keyboard::D){
                pressed_[1] = true;
            }
            if (event.key.code == sf::Keyboard::S){
                pressed_[2] = true;
            }
            if (event.key.code == sf::Keyboard::A){
                pressed_[3] = true;
            }
            if (event.key.code == sf::Keyboard::LShift) {
                speed_ = 10;
            }
            if (event.key.code == sf::Keyboard::LControl) {
                speed_ = 2;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (speed_ != 5) {
                    speed_ = 5;
                } else {
                    speed_ = 100;
                }
            }
        }
        if (event.type == sf::Event::KeyReleased){
            if (event.key.code == sf::Keyboard::W){
                pressed_[0] = false;
            }
            if (event.key.code == sf::Keyboard::D){
                pressed_[1] = false;
            }
            if (event.key.code == sf::Keyboard::S){
                pressed_[2] = false;
            }
            if (event.key.code == sf::Keyboard::A){
                pressed_[3] = false;
            }
            if (event.key.code == sf::Keyboard::LShift) {
                speed_ = 5;
            }
            if (event.key.code == sf::Keyboard::LControl) {
                speed_ = 5;
            }
        }
    }
    if (pressed_[0] != pressed_[2] || pressed_[1] != pressed_[3]) {
        state_ = 1;
        if (pressed_[0] && !pressed_[2]) heading_ = 0;
        if (pressed_[2] && !pressed_[0]) heading_ = 2;
        if (pressed_[1] && !pressed_[3]) heading_ = 1;
        if (pressed_[3] && !pressed_[1]) heading_ = 3;
    } else {
        state_ = 0;
    }
}

void Player::Update(float tick_time) {
    velocity_.x = ((int)pressed_[1] - (int)pressed_[3]) * speed_;
    velocity_.y = ((int)pressed_[2] - (int)pressed_[0]) * speed_;
    Entity::Update(tick_time);
}