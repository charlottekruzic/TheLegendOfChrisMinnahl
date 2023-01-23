#include "title.h"
#include <iostream>
#include <gf/Log.h>

#include "../manager.h"

Title::Title(gf::Vector2i size,Manager& link) :
	Scene(link.getRenderer().getSize()), managerLink(link), font("data/arial.ttf"), buttonStart("Start", font, 30.0), buttonRules("Rules", font, 30.0), buttonQuit("Quit", font, 30.0){
	setClearColor(gf::Color::Gray(0.1f));
	
	//Title
	this->titleMenu = gf::Text("The Legend Of Chris Minnahl", font); 
    this->titleMenu.setColor(gf::Color::White);

	
    //Button
	auto setupButton = [&] (gf::TextButtonWidget& button, auto callback) {
        button.setDefaultTextColor(gf::Color::Black);
        button.setDefaultBackgroundColor(gf::Color::White);
        button.setSelectedTextColor(gf::Color::Black);
        button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
        button.setBackgroundOutlineThickness(2);
        button.setRadius(12.0);
        button.setAnchor(gf::Anchor::TopLeft);
        button.setAlignment(gf::Alignment::Center);
        buttons.addWidget(button);
    };

    setupButton(buttonStart, [&] () {
        gf::Log::debug("Start pressed!\n");
        managerLink.replaceScene(managerLink.gameScene);
    });
	setupButton(buttonRules, [&] () {
        gf::Log::debug("Rules pressed!\n");
        managerLink.replaceScene(managerLink.rulesScene);
    });
	setupButton(buttonQuit, [&] () {
        gf::Log::debug("Quit pressed!\n");
        managerLink.popAllScenes();
    });

	
	
	
}



void Title::renderTitle(gf::RenderTarget &target){
	gf::Coordinates coords(target);
	this->titleMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.07f, 0.07f)).x);
	this->titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
	this->titleMenu.setAnchor(gf::Anchor::TopCenter);
	
	target.draw(this->titleMenu);

}

void Title::renderButtons(gf::RenderTarget &target){
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.075f;
    constexpr float spaceBetweenButton = 0.045f;
    
	this->buttonStart.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonStart.setPosition(coords.getRelativePoint({0.45f, 0.425f}));
    this->buttonStart.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonStart.setPadding(coords.getRelativeSize({0.01f, 0.f}).x);

    this->buttonRules.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonRules.setPosition(coords.getRelativePoint({0.45f, 0.425f + characterSize + spaceBetweenButton}));
    this->buttonRules.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonRules.setPadding(coords.getRelativeSize({0.01f, 0.f}).x);

   this->buttonQuit.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
   this->buttonQuit.setPosition(coords.getRelativePoint({0.45f, 0.425f + (characterSize + spaceBetweenButton) * 2}));
   this->buttonQuit.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
   this->buttonQuit.setPadding(coords.getRelativeSize({0.01f, 0.f}).x);

	target.draw(this->buttonStart);
    target.draw(this->buttonRules);
    target.draw(this->buttonQuit);
}

void Title::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->buttonStart.contains(mouseEvent.coords)){
                this->buttonStart.setSelected();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                this->buttonRules.setSelected();
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                this->buttonQuit.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->buttonStart.setState(gf::WidgetState::Default );
            this->buttonRules.setState(gf::WidgetState::Default );
            this->buttonQuit.setState(gf::WidgetState::Default );

            if(this->buttonStart.contains(mouseEvent.coords)){
                managerLink.replaceScene(managerLink.gameScene);
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                managerLink.replaceScene(managerLink.rulesScene);
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                managerLink.getWindow().close();
            }
            break;
        default:
            break;
    }
}

void Title::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButtons(target);
}