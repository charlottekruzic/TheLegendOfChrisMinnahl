#include "player.h"

Player::Player(gf::Vector2f spawn) : m_velocity(0,0),shape(PLAYER_SIZE) {
    this->speed = 200;
    this->color = gf::Color::Azure;

	//Position du joueur
    this->m_position = spawn;

	//Utilisé pour les collisions (Après)
    this->rect = gf::RectI().fromPositionSize(this->m_position,PLAYER_SIZE);  




	//Shape = la forme visuelle qui va apparaitre a l'ecran
    this->shape.setColor(this->color);
    this->shape.setAnchor(gf::Anchor::TopLeft);
    this->shape.setPosition(this->m_position);

}

void Player::onKeyPress(gf::Event e){
    switch (e.key.keycode){
        case gf::Keycode::Right:
            this->m_velocity.x += this->speed;
            break;
        case gf::Keycode::Left:
            this->m_velocity.x -= this->speed;
            break;
        case gf::Keycode::Up:
            this->m_velocity.y -= this->speed;
            break;
        case gf::Keycode::Down:
            this->m_velocity.y += this->speed;
            break;
        default:
            break;
    }
}
void Player::onKeyRelease(gf::Event e){
    switch (e.key.keycode){
        case gf::Keycode::Right:
            this->m_velocity.x -= this->speed;
            break;
        case gf::Keycode::Left:
            this->m_velocity.x += this->speed;
            break;
        case gf::Keycode::Up:
            this->m_velocity.y += this->speed;
            break;
        case gf::Keycode::Down:
            this->m_velocity.y -= this->speed;
            break;
        default:
            break;
    }
}

void Player::update(float dt){
    this->m_position += this->m_velocity  * dt;
    this->rect = this->rect.fromPositionSize(this->m_position,PLAYER_SIZE);
    this->shape.setPosition(this->m_position);

}

void Player::render(gf::RenderTarget& target){
    target.draw(this->shape);
};

