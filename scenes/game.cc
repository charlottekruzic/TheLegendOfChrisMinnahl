#include "game.h"
#include <iostream>

#include "../manager.h"

<<<<<<< HEAD
Game::Game(gf::Vector2i size,Manager& link) 
: Scene(size)
, echapAction("press echap")
, spaceAction("press Space")
, mAction("Open map")
, rightAction("Go right")
, leftAction("Go left")
, upAction("Go up")
, downAction("Go down")
, managerLink(link)
, level(player)
, m_score("0/0", managerLink.resources.getFont("font/arial.ttf"), 25)
, m_openMap("Open map", managerLink.resources.getFont("font/arial.ttf"), 25)
, m_buttonMap("M", managerLink.resources.getFont("font/arial.ttf"), 25)
{
=======
Game::Game(gf::Vector2i size,Manager& link) :
	Scene(size),
	spaceAction("press Space"),
	rightAction("Go right"),
	leftAction("Go left"), 
	upAction("Go up"),
	downAction("Go down"),
	managerLink(link),
	level(player,map),
	m_font("data/arial.ttf"),
	m_score("0/0", m_font, 25){
>>>>>>> 93e3dcc (re-structured level and decentralized map)

	level_list = {"1.txt","2.txt","3.txt"};
	setClearColor(gf::Color::Black);

	//SET ACTIONS
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	spaceAction.setContinuous();
	addAction(spaceAction);
		
	rightAction.addKeycodeKeyControl(gf::Keycode::Right);
	rightAction.setContinuous();
	addAction(rightAction);

	leftAction.addKeycodeKeyControl(gf::Keycode::Left);
	leftAction.setContinuous();
	addAction(leftAction);

	upAction.addKeycodeKeyControl(gf::Keycode::Up);
	upAction.setContinuous();
	addAction(upAction);

	downAction.addKeycodeKeyControl(gf::Keycode::Down);
	downAction.setContinuous();
	addAction(downAction);

	echapAction.addKeycodeKeyControl(gf::Keycode::Escape);
	echapAction.setInstantaneous();
	addAction(echapAction);

	mAction.addKeycodeKeyControl(gf::Keycode::M);
	mAction.setInstantaneous();
	addAction(mAction);
	
	//INITIALIZE PLAYER
	player.setPosition({100,100});

	//INITIALIZE LEVEL
<<<<<<< HEAD
	level.load("data/TheLegendOfChrisMinnahl/levels/3.txt");
=======
	
>>>>>>> 93e3dcc (re-structured level and decentralized map)

	//SCORE
	m_score.setDefaultTextColor(gf::Color::White);
    m_score.setSelectedTextColor(gf::Color::White);
    m_score.setAnchor(gf::Anchor::TopLeft);
	m_widgets.addWidget(m_score);

	//OPEN MAP
	m_buttonMap.setDefaultTextColor(gf::Color::Black);
    m_buttonMap.setDefaultBackgroundColor(gf::Color::White);
    m_buttonMap.setSelectedTextColor(gf::Color::Black);
    m_buttonMap.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    m_buttonMap.setBackgroundOutlineThickness(2);
    m_buttonMap.setRadius(12.0);
    m_buttonMap.setAnchor(gf::Anchor::BottomLeft);
    m_buttonMap.setAlignment(gf::Alignment::Center);
    m_widgets.addWidget(m_buttonMap);

	m_openMap.setDefaultTextColor(gf::Color::White);
    m_openMap.setSelectedTextColor(gf::Color::White);
    m_openMap.setAnchor(gf::Anchor::BottomLeft);
	m_widgets.addWidget(m_openMap);

	//ADD ENTITIES TO THE WORLD
	addWorldEntity(level);
	addWorldEntity(player);

	init();
	
}
void Game::init(){
	map.load("levels/3.txt");
	level.reset();
}

void Game::reset(){
	desactivateActions();
	level.reset();
}



void Game::doHandleActions(gf::Window & window){
<<<<<<< HEAD
	if(isPaused() || isHidden()){return;}
	player.setWantToStatue(spaceAction.isActive());
	if(rightAction.isActive()){
		player.addVelocity({1,0});
	}
	if(leftAction.isActive()){
		player.addVelocity({-1,0});
	}
	if(upAction.isActive()){
		player.addVelocity({0,-1});
	}
	if(downAction.isActive()){
		player.addVelocity({0,1});
	}
	if(echapAction.isActive()){
		pause();
		managerLink.pushScene(managerLink.pauseScene);
	}

	if(mAction.isActive()){ //&& player.hasMap()
		desactivateActions();
		managerLink.replaceScene(managerLink.mapScene);
	}

	if(level.checkGameOver()){
		managerLink.endScene.setLose();
		managerLink.replaceScene(managerLink.endScene);

	}
	if(level.checkWin()){
		managerLink.endScene.setWin();
		managerLink.replaceScene(managerLink.endScene);

	}
	
}

Level& Game::getLevel(){
	return level;
}

void Game::desactivateActions(){
	rightAction.setInstantaneous();
	leftAction.setInstantaneous();
	upAction.setInstantaneous();
	downAction.setInstantaneous();

	rightAction.reset();
	leftAction.reset();
	upAction.reset();
	downAction.reset();

	rightAction.setContinuous();
	leftAction.setContinuous();
	upAction.setContinuous();
	downAction.setContinuous();	
}

void Game::doUpdate(gf::Time time){
	setWorldViewCenter(player.getPosition());
}

void Game::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
	renderWorldEntities(target,states);
	renderHudEntities(target, states);

	//Score
	gf::Coordinates coords(target);
	int total = (int) map.getObjects().size();
	int found = (int) level.getFoundObjects().size();
	std::string text_score = std::to_string(found) + "/" + std::to_string(total);
	m_score.setString(text_score);
	m_score.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    m_score.setPosition(coords.getRelativePoint({0.05f, 0.05f}));
	target.draw(m_score);

	//Ouverture map
	m_openMap.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    m_openMap.setPosition(coords.getRelativePoint({0.09f, 0.95f}));
	target.draw(m_openMap);

	m_buttonMap.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
	m_buttonMap.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.1f, 0.1f) - 0.1f).x);
    m_buttonMap.setPadding(coords.getRelativeSize({0.01f, 0.01f}).x);
    m_buttonMap.setPosition(coords.getRelativePoint({0.05f, 0.95}));
	target.draw(m_buttonMap);
}
