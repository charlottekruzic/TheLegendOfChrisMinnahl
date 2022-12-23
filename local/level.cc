#include "level.h"
#include <iostream>

Level::Level(gf::Vector2f size, Player* player,gf::Vector2i start, gf::Vector2i end): width(size.x),height(size.y) , player(player){
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::Empty));
        }
    }
    if(!this->setStart(start)){exit(1);}
    if(!this->setEnd(end)){exit(1);}
}


bool Level::addWall(gf::Vector2i position){
	if(this->isFreeSpace(position)){
        this->map[position.y][position.x].setType(WallType::Solid);
		return true;
    }
    return false;
}

bool Level::isFreeSpace(gf::Vector2i position){
    if(position.y < 0 || position.y >= this->height){
        return false;
    }
    if(position.x < 0 || position.x >= this->width){
        return false;
    }
    if(this->map[position.y][position.x].getType() == WallType::Empty){
    	return true;
    }
    return false;
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
    this->handleCollisionX();
    this->handleCollisionY();
}

bool Level::setEnd(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->map[pos.y][pos.x].setType(WallType::End);
		this->end = pos;
		return true;
	}
	return false;
}

bool Level::setStart(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->start = pos;
		this->map[pos.y][pos.x].setType(WallType::Start);
		return true;
	}
	return false;	
}

void Level::render(gf::RenderTarget& target){
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.getType()!=WallType::Empty){
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
            }
            if(this->map[i][j].getRect().intersects(this->player->getRect(),intersection)){
            	return &this->map[i][j];
            }
        }
    }
    return nullptr;
}

void Level::handleCollisionX(){
    Wall* ptr_collider = this->checkCollisions();
    if(ptr_collider==nullptr){return;}
    gf::Vector2f playerVel = this->player->getVelocity();
    if(playerVel.x==0){return;}
    float x = this->player->getPosition()[0];
    float y = this->player->getPosition()[1];
    if(playerVel.x>0){
        //right
        this->player->setPosition({(ptr_collider->getPosition()[0]-PLAYER_SIZE[0]), y});
    }else{
        //left
        this->player->setPosition({(ptr_collider->getPosition()[0]+WALL_SIZE[0]), y});
    }
}


void Level::handleCollisionY(){
    Wall* ptr_collider = this->checkCollisions();
    if(ptr_collider==nullptr){return;}
    gf::Vector2f playerVel = this->player->getVelocity();
    if(playerVel.y==0){return;}
    float x = this->player->getPosition()[0];
    float y = this->player->getPosition()[1];
    if(playerVel.y>0){
        //right
        this->player->setPosition( { x , (ptr_collider->getPosition()[1]-PLAYER_SIZE[1])} );
    }else{
        //left
        this->player->setPosition( { x , (ptr_collider->getPosition()[1]+WALL_SIZE[1]) } );
    }
}
