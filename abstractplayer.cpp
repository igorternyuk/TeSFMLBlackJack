#include "abstractplayer.h"
#include "card.h"
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::AbstractPlayer::AbstractPlayer(const std::string &name):
    m_name{name}, m_hand{std::make_unique<Hand>()}
{}

iat_bj::AbstractPlayer::~AbstractPlayer()
{}

bool iat_bj::AbstractPlayer::isBusted() const
{
    const std::vector<std::unique_ptr<Card>> &cards = m_hand->cards();
    if(cards.size() == 2 && cards[0]->getRank() == Card::Rank::ACE &&
       cards[1]->getRank() == Card::Rank::ACE)
    {
        return false;
    }
    return m_hand->total() > BUSTED_LIMIT;
}

void iat_bj::AbstractPlayer::addCard(std::unique_ptr<Card> &card)
{
    m_hand->add(card);
}

void iat_bj::AbstractPlayer::clearCards()
{
    m_hand->clear();
}

int iat_bj::AbstractPlayer::getHandTotal() const
{
    return m_hand->total();
}

bool iat_bj::AbstractPlayer::hasBlackJack() const
{
    const std::vector<std::unique_ptr<Card>> &cards = m_hand->cards();
    bool hasAceAndFace = cards[0]->getRank() == Card::Rank::ACE &&
                         cards[1]->getRank() >= Card::Rank::JACK;
    bool hasFaceAndAce= cards[1]->getRank() == Card::Rank::ACE &&
                        cards[0]->getRank() >= Card::Rank::JACK;
    bool hasAceAndTen = cards[0]->getRank() == Card::Rank::ACE &&
                         cards[1]->getRank() == Card::Rank::TEN;
    bool hasTenAndAce = cards[1]->getRank() == Card::Rank::ACE &&
                        cards[0]->getRank() == Card::Rank::TEN;
    return (cards.size() == 2 && (hasAceAndFace || hasFaceAndAce || hasAceAndTen || hasTenAndAce));
}

bool iat_bj::AbstractPlayer::hasTwoCardWithSameSuit() const
{
    const std::vector<std::unique_ptr<Card>> &cards = m_hand->cards();
    return (cards.size() == 2 && cards[0]->getSuit() == cards[1]->getSuit());

}

bool iat_bj::AbstractPlayer::hasTwoAces() const
{
    const std::vector<std::unique_ptr<Card>> &cards = m_hand->cards();
    return cards.size() == 2 && cards[0]->getRank() == Card::Rank::ACE &&
           cards[1]->getRank() == Card::Rank::ACE;
}

bool iat_bj::AbstractPlayer::hasThreeSevens() const
{
    const std::vector<std::unique_ptr<Card>> &cards = m_hand->cards();
    return cards.size() == 3 &&
           cards[0]->getRank() == Card::Rank::SEVEN &&
           cards[1]->getRank() == Card::Rank::SEVEN &&
           cards[2]->getRank() == Card::Rank::SEVEN;
}

std::string iat_bj::AbstractPlayer::getHandTextDescription() const
{
    return m_name + std::string(": ") + m_hand->textDescription();
}
