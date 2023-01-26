#include "pause.h"
#include <iostream>

#include "../manager.h"

Pause::Pause(gf::Vector2i size,Manager& link) 
: Scene(link.getRenderer().getSize())
, managerLink(link)
, buttonRestart("Restart", managerLink.resources.getFont("font/arial.ttf"))
, buttonResume("Resume", managerLink.resources.getFont("font/arial.ttf"))
, buttonRules("Rules", managerLink.resources.getFont("font/arial.ttf"))
, buttonMenu("Menu", managerLink.resources.getFont("font/arial.ttf")){
	setClearColor(gf::Color::Black);

    this->pause=false;

	//Title
	this->titleMenu = gf::Text("Pause", managerLink.resources.getFont("font/arial.ttf")); 
    this->titleMenu.setColor(gf::Color::White);

	
    //Button
	setButton(this->buttonRestart);
    setButton(this->buttonResume);
    setButton(this->buttonRules);
    setButton(this->buttonMenu);
	
	
}

void Pause::setButton(gf::TextButtonWidget &button){
    button.setDefaultTextColor(gf::Color::Black);
    button.setDefaultBackgroundColor(gf::Color::White);
    button.setSelectedTextColor(gf::Color::Black);
    button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    button.setBackgroundOutlineThickness(2);
    button.setRadius(12.0);
    button.setAnchor(gf::Anchor::TopLeft);
    button.setAlignment(gf::Alignment::Center);
    this->buttons.addWidget(button);

}

bool Pause::isPause(){
	return pause;
}

void Pause::setPause(bool var){
    pause = var;
}

void Pause::renderTitle(gf::RenderTarget &target){
	gf::Coordinates coords(target);
	this->titleMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.06f, 0.06f)).x);
	this->titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.26f }));
	this->titleMenu.setAnchor(gf::Anchor::TopCenter);
	
	target.draw(this->titleMenu);

}

void Pause::renderButtons(gf::RenderTarget &target){
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.03f;
    constexpr float spaceBetweenButton = 0.06f;
    const float paddingSize = coords.getRelativeSize({0.02f, 0.f}).x;
    
	this->buttonRestart.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonRestart.setPosition(coords.getRelativePoint({0.5f, 0.4f}));
    this->buttonRestart.setAnchor(gf::Anchor::TopCenter);
    this->buttonRestart.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonRestart.setPadding(paddingSize);

    this->buttonResume.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonResume.setPosition(coords.getRelativePoint({0.5f, 0.4f + characterSize + spaceBetweenButton}));
    this->buttonResume.setAnchor(gf::Anchor::TopCenter);
    this->buttonResume.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonResume.setPadding(paddingSize);

    this->buttonRules.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonRules.setPosition(coords.getRelativePoint({0.5f, 0.4f + (characterSize + spaceBetweenButton) * 2}));
    this->buttonRules.setAnchor(gf::Anchor::TopCenter);
    this->buttonRules.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonRules.setPadding(paddingSize);

    this->buttonMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonMenu.setPosition(coords.getRelativePoint({0.5f, 0.4f + (characterSize + spaceBetweenButton) * 3}));
    this->buttonMenu.setAnchor(gf::Anchor::TopCenter);
    this->buttonMenu.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonMenu.setPadding(paddingSize);

	target.draw(this->buttonRestart);
    target.draw(this->buttonResume);
    target.draw(this->buttonRules);
    target.draw(this->buttonMenu);
}

void Pause::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->buttonRestart.contains(mouseEvent.coords)){
                this->buttonRestart.setSelected();
            }else if(this->buttonResume.contains(mouseEvent.coords)){
                this->buttonResume.setSelected();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                this->buttonRules.setSelected();
            }else if(this->buttonMenu.contains(mouseEvent.coords)){
                this->buttonMenu.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->buttonRestart.setState(gf::WidgetState::Default );
            this->buttonResume.setState(gf::WidgetState::Default );
            this->buttonRules.setState(gf::WidgetState::Default );
            this->buttonMenu.setState(gf::WidgetState::Default );


            if(this->buttonRestart.contains(mouseEvent.coords)){
                managerLink.gameScene.reset();
                managerLink.replaceAllScenes(managerLink.gameScene);
            }else if(this->buttonResume.contains(mouseEvent.coords)){
                managerLink.popScene();
                managerLink.gameScene.resume();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                setPause(true);
                managerLink.replaceAllScenes(managerLink.rulesScene);
            }else if(this->buttonMenu.contains(mouseEvent.coords)){
              
                managerLink.gameScene.reset();
                managerLink.replaceAllScenes(managerLink.titleScene);
            }
            break;
        default:
            break;
    }
}

void Pause::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButtons(target);
}