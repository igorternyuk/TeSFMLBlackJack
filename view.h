#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "card.h"
#include "model.h"
#include "modellistener.h"

#include <vector>
#include <memory>
#include <string>

namespace iat_bj
{
class ConstantModelInterface;
class Controller;

class View: public ModelListener
{
    public:
        explicit View(std::shared_ptr<ConstantModelInterface> spConstantModel,
                      std::shared_ptr<Controller> spController);
        ~View();
        View(const View&) = delete;
        View& operator=(const View&) = delete;
        View(View&&) = delete;
        View& operator=(View&&) = delete;
        void run();
        // ModelListener interface
        virtual void updateView();
    private:
        enum {
            WINDOW_WIDTH = 1200,
            WINDOW_HEIGHT = 600,
            WINDOW_X = 0/*(1366 - WINDOW_WIDTH) / 2*/,
            WINDOW_Y = (768 - WINDOW_HEIGHT) / 2,
            CARD_WIDTH = 73,
            CARD_HEIGHT = 98
        };
        std::shared_ptr<ConstantModelInterface> m_spConstantModel;
        std::shared_ptr<Controller> m_spController;
        const sf::Color m_bgColor{sf::Color(30, 174, 124)};
        const std::string WINDOW_TITLE{"TeBlackJack"};
        const std::string PATH_TO_FONT{"resources/fonts/BRLNSR.TTF"};
        const std::string PATH_TO_BACKGROUND_MUSIC{"resources/sounds/bgm_casino.ogg"};
        std::vector<sf::Sprite> m_btnSprites;
        std::vector<sf::Texture> m_btnTexures;
        mutable sf::RenderWindow m_window;
        mutable sf::Sprite m_spriteCards;
        mutable sf::Sprite m_spriteCardBack;
        sf::Texture m_tCards;
        sf::Texture m_tCardBack;
        sf::Font m_font;
        //Music
        sf::Music m_bgm;
        bool m_haveToDraw{true};
        void loadCardsTexture();
        void loadButtonTextures();
        void userInputPhase();
        void drawingPhase();
        void drawHand(const AbstractPlayer &player, int left, int top) const;
        void drawCards() const;
        void drawTitleAndRoundsNumber() const;
        void drawButtons() const;
    };
}


