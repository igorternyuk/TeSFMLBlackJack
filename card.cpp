#include "card.h"
#include <sstream>
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Card::Card(Card::Rank rank, Card::Suit suit, bool isFaceUp):
    rank_{rank}, suit_{suit}, isFaceUp_{isFaceUp}
{

}

int iat_bj::Card::getValue() const noexcept
{
    int val{0};
    if(isFaceUp_)
    {
        if(rank_ == Rank::ACE)
            val = 11;
        else if(static_cast<int>(rank_)< static_cast<int>(Rank::JACK))
            val = static_cast<int>(rank_) + 1;
        else
            val = 10;
    }
    return val;
}

std::string iat_bj::Card::toString() const noexcept
{
    std::ostringstream ss;
    if(isFaceUp_)
    {
        switch(rank_)
        {
            case Rank::ACE:
                ss << "A";
            break;
            case Rank::TWO:
            case Rank::THREE:
            case Rank::FOUR:
            case Rank::FIVE:
            case Rank::SIX:
            case Rank::SEVEN:
            case Rank::EIGHT:
            case Rank::NINE:
            case Rank::TEN:
                ss << 1 + static_cast<int>(rank_);
            break;
            case Rank::JACK:
                ss << "J";
            break;
            case Rank::QUEEN:
                ss << "Q";
            break;
            case Rank::KING:
                ss << "K";
            break;
            default:
                break;
        }

        switch(suit_)
        {
            case Suit::CLUBS:
                ss << "c";
            break;
            case Suit::DIAMONDS:
                ss << "d";
            break;
            case Suit::HEARTS:
                ss << "h";
            break;
            case Suit::SPADES:
                ss << "s";
            break;
            default:
                break;
        }
    }
    else
    {
        ss << "XX";
    }

    return ss.str();
}
