#include "hand.h"
#include "card.h"

#include <sstream>
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Hand::Hand()
{
    m_cards.reserve(NUM_CARDS_MAX);
}

iat_bj::Hand::~Hand()
{
#ifdef DEBUG
   std::cout << "Hand destructor was called" << std::endl;
#endif
}

void iat_bj::Hand::add(std::unique_ptr<Card> &upCard)
{
    if(m_cards.size() < NUM_CARDS_MAX)
        m_cards.push_back(std::move(upCard));
}

void iat_bj::Hand::clear()
{
    m_cards.clear();
}

int iat_bj::Hand::total() const
{
    //If there are no cards in hand or first card is face down we will return 0
    if(m_cards.empty() || m_cards[0]->getValue() == 0)
        return 0;
    int total{0};
    int numAces{0};
    for(auto it = m_cards.cbegin(); it != m_cards.end(); ++it)
    {
        total += (*it)->getValue();
        if((*it)->getRank() == Card::Rank::ACE)
            ++numAces;
    }
    /*Значения очков каждой карты: от двойки до десятки — соответственно от 2 до 10,
     *  у туза — 1 или 11 (11 пока общая сумма не больше 21, далее 1),
     *  у т. н. картинок (король, дама, валет) — 10.*/
    if(numAces > 0 && total > NO_BUSTED_LIMIT)
        total += numAces - numAces * Card::BIG_ACE_VALUE;
    return total;
}

void iat_bj::Hand::flipFistCard()
{
    m_cards[0]->flip();
}

std::string iat_bj::Hand::textDescription() const
{
   std::ostringstream oss;
   for(const auto &card: m_cards)
   {
       oss << card->toString() << " ";
   }
   oss << "(" << total() << ")";
   return oss.str();
}
