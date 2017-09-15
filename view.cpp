#include "view.h"
#include "controller.h"
#include "constantmodelinterface.h"
#include <ctime>
#include <algorithm>
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::View::View(std::shared_ptr<ConstantModelInterface> spConstantModel,
           std::shared_ptr<Controller> spController):
    m_spConstantModel{spConstantModel},
    m_spController{spController},
    m_window{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE}
{
    loadCardsTexture();
    loadButtonTextures();
    m_font.loadFromFile(PATH_TO_FONT);
    m_window.setPosition(sf::Vector2i{WINDOW_X, WINDOW_Y});
    m_bgm.openFromFile(PATH_TO_BACKGROUND_MUSIC);
    m_bgm.setLoop(true);
    m_spController->startNewRound();
}

iat_bj::View::~View()
{
#ifdef DEBUG
    std::cout << "View destructor was called" << std::endl;
#endif
}


void iat_bj::View::run()
{
    //Main loop of the game
    m_bgm.play();
    while(m_window.isOpen())
    {
        userInputPhase();
        if(m_haveToDraw)
            drawingPhase();
        m_window.display();
    }
    m_bgm.stop();
}

void iat_bj::View::loadCardsTexture()
{
    static const std::string PATH_TO_CARDS_SET{"resources/gfx/CardsSprite.png"};
    static const std::string PATH_TO_CARD_BACK_IMAGE{"resources/gfx/cardBack.png"};

    m_tCards.loadFromFile(PATH_TO_CARDS_SET);
    m_tCards.setSmooth(true);
    m_spriteCards.setTexture(m_tCards);

    m_tCardBack.loadFromFile(PATH_TO_CARD_BACK_IMAGE);
    m_tCardBack.setSmooth(true);
    m_spriteCardBack.setTexture(m_tCardBack);
}

void iat_bj::View::loadButtonTextures()
{
    static const std::vector<std::string> m_btnImagePathes
    {
       "resources/gfx/newRound.png",
       "resources/gfx/hitMe.png",
       "resources/gfx/stand.png",
       "resources/gfx/quitGame.png"
    };

    static const std::vector<std::pair<int, int>> btnLocation
    {
        {195, WINDOW_HEIGHT - 70}, {410, WINDOW_HEIGHT - 70},
        {625, WINDOW_HEIGHT - 70}, {840, WINDOW_HEIGHT - 70}
    };

    for(unsigned short int i{0}; i < m_btnImagePathes.size(); ++i)
    {
        sf::Texture texture;
        texture.loadFromFile(m_btnImagePathes[i]);
        texture.setSmooth(true);
        m_btnTexures.push_back(texture);
    }

    for(unsigned short int i{0}; i < m_btnTexures.size(); ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(m_btnTexures[i]);
        sprite.setPosition(btnLocation[i].first, btnLocation[i].second);
        m_btnSprites.push_back(sprite);
    }
}

void iat_bj::View::userInputPhase()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if(event.type == sf::Event::Resized)
        {
            updateView();
        }
        else if(event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Space:
                    m_spController->startNewRound();
                    break;
                case sf::Keyboard::Right:
                    m_spController->sayHitMe();
                    break;
                case sf::Keyboard::Return:
                    m_spController->sayStand();
                    break;
                case sf::Keyboard::Escape:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                int x{event.mouseButton.x};
                int y{event.mouseButton.y};
                for(unsigned short int i{0}; i < m_btnSprites.size(); ++i)
                {
                    if(m_btnSprites[i].getGlobalBounds().contains(x,y))
                    {
                        switch(i)
                        {
                            case 0:
                                m_spController->startNewRound();
                                break;
                            case 1:
                                m_spController->sayHitMe();
                                break;
                            case 2:
                                m_spController->sayStand();
                                break;
                            case 3:
                                m_window.close();
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}

void iat_bj::View::drawingPhase()
{
    m_window.clear(m_bgColor);
    drawCards();
    drawTitleAndRoundsNumber();
    drawButtons();
    m_haveToDraw = false;
}

void iat_bj::View::drawButtons() const
{
    for(const auto &s: m_btnSprites)
        m_window.draw(s);
}

void iat_bj::View::drawCards() const
{
    static const std::vector<std::pair<int, int>> locations
    {
        {400, 280}, {5, 100}, {5, 280}, {800, 100}, {800, 280}
    };
    const std::vector<std::unique_ptr<Player>> &players = m_spConstantModel->players();
    for(int i = 0; i < m_spConstantModel->numPlayers(); ++i)
    {
        drawHand(*(players[i]), locations[i].first, locations[i].second);
    }
    drawHand(*(m_spConstantModel->dealer()), 400, 100);
}

void iat_bj::View::drawTitleAndRoundsNumber() const
{
    sf::Text title(std::string("BlackJack"), m_font, 70);
    title.setColor(sf::Color(127, 0, 0));
    title.setPosition((WINDOW_WIDTH - title.getGlobalBounds().width) / 2, 10);
    m_window.draw(title);
    sf::Text text(std::string("Round ") + std::to_string(m_spConstantModel->numRounds()),
                  m_font, 60);
    text.setColor(sf::Color(0, 127, 0));
    text.setPosition((WINDOW_WIDTH - text.getGlobalBounds().width) / 2, 450);
    m_window.draw(text);
}

void iat_bj::View::drawHand(const AbstractPlayer &player, int left, int top) const
{
    const std::vector<std::unique_ptr<Card>>& cards = player.getCards();
    for(unsigned short int i{0}; i < cards.size(); ++i)
    {
        if(cards.at(i)->isFaceUp())
        {
            //x and y - coordinates of the card on the sprite
            int x = static_cast<int>(cards.at(i)->getRank());
            int y = static_cast<int>(cards.at(i)->getSuit());
            m_spriteCards.setTextureRect(sf::IntRect{x * CARD_WIDTH,
                                                     y * CARD_HEIGHT,
                                                     CARD_WIDTH + 1,
                                                     CARD_HEIGHT + 1});
            m_spriteCards.setPosition(left + i * (CARD_WIDTH + 1), top);
            m_window.draw(m_spriteCards);
        }
        else
        {
            m_spriteCardBack.setPosition(left + i * (CARD_WIDTH + 1), top);
            m_window.draw(m_spriteCardBack);
        }

        sf::Text playerHandDescription(player.getHandTextDescription(),
                                       m_font, 30);
        playerHandDescription.setColor(sf::Color::Blue);
        playerHandDescription.setPosition(left, top + CARD_HEIGHT + 5);
        m_window.draw(playerHandDescription);
    }
}


void iat_bj::View::updateView()
{
    m_haveToDraw = true;
}
