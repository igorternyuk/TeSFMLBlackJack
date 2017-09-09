#include "deck.h"
#include <card.h>
#include <algorithm>
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Deck::Deck()
{
    m_cards.reserve(NUM_CARDS);
}

iat_bj::Deck::~Deck()
{
#ifdef DEBUG
   std::cout << "Deck destructor was called" << std::endl;
#endif
}

void iat_bj::Deck::populate()
{
    m_cards.clear();
    for(int s {static_cast<int>(Card::Suit::CLUBS)};
        s < static_cast<int>(Card::Suit::SPADES); ++s)
    {
        for(int r{static_cast<int>(Card::Rank::ACE)};
            r <= static_cast<int>(Card::Rank::KING); ++r)
        {
            m_cards.push_back(std::make_unique<Card>(static_cast<Card::Rank>(r),
                                                     static_cast<Card::Suit>(s),
                                                     true));
        }
    }
}

void iat_bj::Deck::shuffle()
{
    std::random_shuffle(m_cards.begin(), m_cards.end());
}

void iat_bj::Deck::deal(AbstractPlayer &player)
{
    if(m_cards.size() > 0)
    {
        player.addCard(m_cards.back());
        m_cards.pop_back();
    }
}
