#ifndef TITLE_H
#define TITLE_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Color.h>
struct Manager;

class Title : public gf::Scene {
	private:
	gf::Action spaceAction; 
	Manager& managerLink;


	public:
	Title(gf::Vector2i size, Manager& managerLink);
	void doHandleActions(gf::Window & window);
};

#endif
