#include "level.h"
#include <iostream>

Level::Level(gf::Vector2f size, Player* player): width(size.x),height(size.y) , player(player){
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::Empty));
        }
    }
}

bool Level::addWall(gf::Vector2i position){
    if(position.y < 0 || position.y >= this->height){
        return false;
    }
    if(position.x < 0 || position.x >= this->width){
        return false;
    }

    if(!this->map[position.y][position.x].isSolid()){
        this->map[position.y][position.x].setType(WallType::Solid);
    }
    return true;
}


bool Level::removeWall(gf::Vector2i position){
    return false;
}

void Level::prettyPrint(){
    std::cout << "-----------------------------------------\n";
    for(auto line : this->map){
        for(auto item : line){
            if(item.isSolid()){
                std::cout << "X|";
            }else{
                std::cout << " |";
            }
        }
        std::cout << "\n";
    }
}

void Level::update(float dt){
    handleCollisionX();
    handleCollisionY();
}

void Level::render(gf::RenderTarget& target){
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.isSolid()){
            	item.render(target);
        	}
        }
    }
}

Wall* Level::checkCollisions(){
    for(int i=0;i<this->map.size();i++){
        for(int j=0;j<this->map[i].size();j++){
            gf::Rect<int> intersection;
            if(!this->map[i][j].isSolid()){
                continue;
            }else{
                if(this->map[i][j].getRect().intersects(this->player->getRect(),intersection)){
                    return &this->map[i][j];
                }
            }
        }
    }
    return nullptr;
}

void Level::handleCollisionX(){
    Wall* ptr_collider = checkCollisions();
    if(ptr_collider==nullptr){
        return;
    }
    Wall collider = *ptr_collider;
    if(this->player->getVelocity()[0]!=0){
        float x = this->player->getPosition()[0];
        float y = this->player->getPosition()[1];
        if(this->player->getVelocity()[0]>0){
            //right
            gf::Vector2f new_position = {(collider.getPosition()[0]-PLAYER_SIZE[0]), y};
            this->player->setPosition(new_position);
        }else{
            //left
            gf::Vector2f new_position = {(collider.getPosition()[0]+WALL_SIZE[0]), y};
            this->player->setPosition(new_position);
        }
    }
}


void Level::handleCollisionY(){
    Wall* ptr_collider = checkCollisions();
    if(checkCollisions()==nullptr){
        return;
    }
    Wall collider = *ptr_collider;
    if(this->player->getVelocity()[1]!=0){
        float x = this->player->getPosition()[0];
        float y = this->player->getPosition()[1];
        if(this->player->getVelocity()[1]>0){
            //bottom
            gf::Vector2f new_position = {x, (collider.getPosition()[1]-PLAYER_SIZE[1])};
            this->player->setPosition(new_position);
        }else{
            //top
            gf::Vector2f new_position = {x, (collider.getPosition()[1]+WALL_SIZE[1])};
            this->player->setPosition(new_position);
            
        }
    }
}