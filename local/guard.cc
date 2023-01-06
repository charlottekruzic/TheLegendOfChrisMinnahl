#include "guard.h"
#include <iostream>

struct RouteAction* generateRouteAction(actionType type,float time,gf::Vector2i position){
	struct RouteAction* newRoute = new struct RouteAction;
	newRoute->type = type;
	newRoute->time = time;
	newRoute->grid_position = position;
	return newRoute;
}

Guard::Guard():velocity(0,0),shape(GUARD_SIZE){
    speed = 200;
    position = {0,0};
    velocity = {0,0};
    rect = gf::RectI().fromPositionSize(position,GUARD_SIZE);  
    color = gf::Color::Red;
   	shape.setColor(color);
    shape.setAnchor(gf::Anchor::TopLeft);
    shape.setPosition(position);
}


void Guard::setRoute(std::vector<RouteAction *> new_route){
	route = new_route;
	route_index = -1;
	nextAction();//initialize first action

	
}


void Guard::nextAction(){
	route_index ++;
   	if(route_index >= route.size()){
   		route_index = 0;
   	}


    currentAction = route[route_index];
   	currentAction->cumulated_time = 0;

    std::cout << "Route index : "<< route_index <<"\n";
	std::cout << "New action ! "<< (currentAction->type == actionType::GO ?  "GO" : "WAIT") <<"\n";
	std::cout << "time : " << currentAction->time << "\n";
	
   	switch(currentAction->type){
   		case actionType::WAIT:
   			shape.setColor(gf::Color::Azure);
   			break;
   	   	case actionType::GO:
   	   	   	shape.setColor(gf::Color::Red);

   			break;
   		default:
   			break;
   	}

}

void Guard::update(float dt){

    switch(currentAction->type){
    	case actionType::WAIT:
    		break;
    	case actionType::GO:
    		break;
    	default:
    		break;
    }

    currentAction->cumulated_time += dt;



	//unchanged
    position += velocity  * dt;
   	rect = rect.fromPositionSize(position,GUARD_SIZE);
    shape.setPosition(position);
    
    if (currentAction->cumulated_time >= currentAction->time){
		nextAction();
    }
}

void Guard::render(gf::RenderTarget& target){
    target.draw(shape);
};

