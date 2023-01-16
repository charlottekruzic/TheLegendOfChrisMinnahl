#ifndef LOCAL_PLAYER_H
#define LOCAL_PLAYER_H
#include <gf/Action.h>
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <iostream>
#include <fstream>
#include "wall.h"

constexpr gf::Vector2i PLAYER_SIZE = {32,32};

class Player : public gf::Entity{
    private:
        gf::Vector2f position;
        gf::Vector2f velocity;
        double speed;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;
        gf::Action leftAction, rightAction, upAction, downAction, spaceAction;
        gf::ActionContainer actions;
        bool hasObject;
        bool isStatue;

        
        
    public:
        Player(gf::Vector2f spawn);
        gf::Vector2f getPosition();
        gf::Vector2f getVelocity();
        gf::RectI * getRect();

        void findObject();
        bool stoleTheObject();

        void isAStatue();
        bool isAStatueBool();

        void setPosition(gf::Vector2f position);
        void setVelocity(gf::Vector2f velocity);

        void reset();

		void processEvent(gf::Event);

		void moveX(float dt);
		void moveY(float dt);
        void handleCollisionX(Wall * collider);
        void handleCollisionY(Wall * collider);

        virtual void update(float dt);
        virtual void render(gf::RenderTarget& target);
};
#endif
