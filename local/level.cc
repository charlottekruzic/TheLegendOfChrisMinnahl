#include "level.h"
#include <iostream>

Level::Level(gf::Vector2f size, Player* player,gf::Vector2i start, gf::Vector2i end, gf::Vector2i object): width(size.x),height(size.y) , player(player){
    this->win=false; 
    this->loose = false;
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::EMPTY));
        }
    }
    if(!this->setStart(start)){exit(1);}
    if(!this->setEnd(end)){exit(1);}
    if(!this->setObject(object)){exit(1);}	
}

void Level::reset(){	
    this->player->reset();
    this->player->setPosition(this->start * WALL_SIZE);
    this->setObject(object);
    this->win=false;
    this->loose = false;
    for (auto guard : guards){
    	guard->reset();
    }
}

bool Level::isWin(){
    return this->win;
}
bool Level::isLoose(){
    return this->loose;
}

Guard * Level::addGuard(gf::Vector2i grid_pos,std::vector<RouteAction *> newRoute){
	Guard *newGuard = new Guard(grid_pos);
	newGuard->setRoute(newRoute);
	guards.push_back(newGuard);
	return newGuard;
}

bool Level::addWall(gf::Vector2i position){
	if(this->isFreeSpace(position)){
        this->map[position.y][position.x].setType(WallType::SOLID);
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
    if(this->map[position.y][position.x].getType() == WallType::EMPTY){
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
    for (auto guard : guards){
    	(*guard).update(dt);
    }
	this->player->moveX(dt);
    this->player->handleCollisionX(this->checkCollisions());
	this->player->moveY(dt);
    this->player->handleCollisionY(this->checkCollisions());
    this->checkTakeObject();
    if (!this->checkWin()){
    	this->checkLoose();
    }

}

bool Level::setEnd(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->map[pos.x][pos.y].setType(WallType::END);
		this->end = pos;  
		return true;
	}
	return false;
}

bool Level::setStart(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->start = pos;
		this->map[pos.x][pos.y].setType(WallType::START);
        
		return true;
	}
	return false;	
}

bool Level::setObject(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->object = pos;
		this->map[pos.x][pos.y].setType(WallType::OBJECT);
		return true;
	}
	return false;	
}

void Level::render(gf::RenderTarget& target){
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.getType()!=WallType::EMPTY){
            	item.render(target);
        	}
        }
    }
    for (auto& guard : guards){
    	(*guard).render(target);
    }

}

Wall* Level::checkCollisions(){
    for(int i=0;i<this->map.size();i++){
        for(int j=0;j<this->map[i].size();j++){
            gf::Rect<int> intersection;
            
            if(!this->map[i][j].isSolid()){
                continue;
            }
            if(this->map[i][j].getRect().intersects(*(player->getRect()),intersection)){
            	return &this->map[i][j];
            }
        }
    }
    return nullptr;
}
bool Level::checkWin(){
    Wall square_end = this->map[end[0]][end[1]];
    gf::Rect<int> rect_intersection;
   	gf::Rect<int> *  playerRect = player->getRect();

    if(this->player->stoleTheObject()==true && square_end.getRect().intersects(*playerRect,rect_intersection)==true){
        this->win=true;
        return true;
    }
    return false;
}

bool Level::checkLoose(){
    gf::Rect<int> rect_intersection;
	gf::Rect<int>* playerRect = player->getRect();
	for (auto& guard : guards){

		if(playerRect->intersects(*guard->getRect(),rect_intersection)){
			this->loose = true;
			return true;
		}
	}
	return false;
}


void Level::checkTakeObject(){
    Wall square_object = this->map[object[0]][object[1]];
    gf::Rect<int> rect_intersection;
    if(square_object.getRect().intersects(*(this->player->getRect()),rect_intersection)==true){
        this->player->findObject();
        this->map[object[0]][object[1]].setType(WallType::EMPTY);
    }
}



