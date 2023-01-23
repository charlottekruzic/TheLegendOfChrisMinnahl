#ifndef END_H
#define END_H

#include "local/level.h"

#include <gf/Scene.h>
#include <gf/Color.h>
#include <gf/Widgets.h>
#include <gf/Font.h>
#include <gf/Text.h>
#include <gf/Coordinates.h>
#include <gf/WidgetContainer.h>

struct Manager;

class End : public gf::Scene {
	private:
		Manager& m_managerLink;
        gf::Action m_spaceAction;
        gf::Font m_font = gf::Font("data/arial.ttf");
        gf::Text m_text_win;
        gf::Text m_text_lose;
        gf::TextButtonWidget m_menuButton;
        gf::TextButtonWidget m_restartButton;
		gf::WidgetContainer m_widgets;
        void setButton(gf::TextButtonWidget &button);
        Level& m_level;

	
	public:
		End(gf::Vector2i size,Manager& link);
        void doHandleActions(gf::Window & window) override;
        void doProcessEvent(gf::Event& event) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif