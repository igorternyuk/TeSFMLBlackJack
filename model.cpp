#include "model.h"
#include "card.h"
#include <algorithm>
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Model::Model():
    m_deck{std::make_unique<Deck>()},
    m_dealer{std::make_unique<Dealer>("Dealer")}
{
    //Add players to the list
    m_players.reserve(NUM_PLAYERS);
    m_players.push_back(std::make_unique<Player>("You", INIT_PLAYER_MONEY,
                                                 Player::Type::HUMAN));
    for(unsigned short int i{1}; i < NUM_PLAYERS; ++i)
        m_players.push_back(std::make_unique<Player>(std::string("Bot") +
                                                     std::to_string(i),
                                                     INIT_PLAYER_MONEY));
}

iat_bj::Model::~Model()
{
#ifdef DEBUG
    std::cout << "Model destructor was called" << std::endl;
#endif
}

void iat_bj::Model::startNewRound()
{
    //Remove everyones's cards
    ++m_numRounds;
    for(auto it = m_players.begin(); it != m_players.end(); ++it)
    {
        (*it)->clearCards();
        (*it)->bet();
        (*it)->setStatus(Player::Status::HITTING);
    }
    m_dealer->clearCards();
    m_deck->populate();
    m_deck->shuffle();

    // deal initial 2 cards to everyone
    for(unsigned short int i{0}; i < NUM_CARDS_INIT; ++i)
    {
        for(auto it = m_players.begin(); it != m_players.end(); ++it)
        {
            m_deck->deal(*(*it));
        }
        m_deck->deal(*m_dealer);
    }
    m_dealer->flipFirstCard();
    notifyAllListeners();
}

void iat_bj::Model::hit()
{
    if(m_players[0]->getStatus() == Player::Status::HITTING)
    {
        m_deck->deal(*(m_players[0]));
        notifyAllListeners();
    }
    if(m_players[0]->isBusted())
    {
        m_players[0]->setStatus(Player::Status::LOST);
        dealToBotsAndDealer();
        checkWinners();
        notifyAllListeners();
    }
}

void iat_bj::Model::stand()
{
    if(m_players[0]->getStatus() == Player::Status::HITTING)
    {
        m_players[0]->setStatus(Player::Status::STAND);
        dealToBotsAndDealer();
        checkWinners();
        notifyAllListeners();
    }
}

void iat_bj::Model::addListener(std::shared_ptr<ModelListener> spListener)
{
    m_listeners.push_back(spListener);
}

void iat_bj::Model::removeListener(std::shared_ptr<ModelListener> spListener)
{
    m_listeners.remove_if([spListener](std::weak_ptr<ModelListener> p){
        return !(p.owner_before(spListener) || spListener.owner_before(p));
    });
}

void iat_bj::Model::checkWinners()
{
    if(m_dealer->hasTwoAces())
    {
        for(auto &p: m_players)
        {
            if(p->hasTwoAces())
            {
                p->setStatus(Player::Status::PUSH);
                p->giveBetBack();
            }
            else
            {
                p->setStatus(Player::Status::LOST);
                m_dealer->takeLosersBet(p->getBetValue());
            }
        }
    }
    else if(m_dealer->hasBlackJack())
    {
        for(auto &p: m_players)
        {
            if(p->hasTwoAces())
            {
                p->setStatus(Player::Status::WON);
                p->award(COEF_WIN_TWO_ACES);
                m_dealer->payToWinner(COEF_WIN_TWO_ACES * p->getBetValue());
            }
            else if(p->hasBlackJack())
            {
                p->setStatus(Player::Status::PUSH);
                p->giveBetBack();
            }
            else
            {
                p->setStatus(Player::Status::LOST);
                m_dealer->takeLosersBet(p->getBetValue());
            }
        }
    }
    else if(m_dealer->isBusted())
    {
        for(auto &p: m_players)
        {
            if(p->isBusted())
            {
               p->setStatus(Player::Status::LOST);
               m_dealer->takeLosersBet(p->getBetValue());
            }
            else
            {
                p->setStatus(Player::Status::WON);
                awardWinner(*p);
            }
        }
    }
    else
    {
        int dTotal = m_dealer->getHandTotal();
        for(auto &p: m_players)
        {
            if(p->isBusted())
            {
                p->setStatus(Player::Status::LOST);
                m_dealer->takeLosersBet(p->getBetValue());
            }
            else if(p->getHandTotal() > dTotal)
            {
                p->setStatus(Player::Status::WON);
                awardWinner(*p);
            }
            else if(p->getHandTotal() == dTotal)
            {
                p->setStatus(Player::Status::PUSH);
                p->giveBetBack();
            }
            else if(p->getHandTotal() < dTotal){
                p->setStatus(Player::Status::LOST);
                m_dealer->takeLosersBet(p->getBetValue());
            }
        }
    }
}

void iat_bj::Model::dealToBotsAndDealer()
{
    for(unsigned short int i{1}; i < NUM_PLAYERS; ++i)
    {
        while (m_players[i]->isHitting()) {
            m_deck->deal(*(m_players[i]));
        }
        m_players[i]->setStatus(Player::Status::STAND);
    }
    //Если поменяешь местами следующие две иструкции получишь сегфолт
    m_dealer->flipFirstCard();
    while (m_dealer->isHitting()) {
        m_deck->deal(*m_dealer);
    }
}

void iat_bj::Model::awardWinner(Player &p)
{
    if(p.getStatus() != Player::Status::WON)
        return;
    if(p.hasTwoAces())
    {
        p.award(COEF_WIN_TWO_ACES);
        m_dealer->payToWinner(COEF_WIN_TWO_ACES * p.getBetValue());
    }
    else if(p.hasBlackJack())
    {
        p.award(COEF_WIN_BLACK_JACK);
        p.addBonus(BONUS_BLACKJACK_SAME_SUIT);
        m_dealer->payToWinner(BONUS_BLACKJACK_SAME_SUIT);
        m_dealer->payToWinner(COEF_WIN_BLACK_JACK * p.getBetValue());
    }
    else
    {
        p.award(COEF_WIN);
        m_dealer->payToWinner(p.getBetValue());
        if(p.hasThreeSevens())
        {
            p.addBonus(BONUS777);
            m_dealer->payToWinner(BONUS777);
        }
    }
}

void iat_bj::Model::notifyAllListeners()
{
    for(const auto &l: m_listeners)
    {
        if(!l.expired())
        {
            auto spListener = l.lock();
            spListener->updateView();
        }
    }
}
