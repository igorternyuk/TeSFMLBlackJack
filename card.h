#pragma once

#include <string>

namespace iat_bj
{
    class Card
    {
    public:
        enum class Rank
        {
            ACE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING
        };

        enum class Suit
        {
            CLUBS,
            HEARTS,
            SPADES,
            DIAMONDS
        };
        enum { BIG_ACE_VALUE = 11 };
        explicit Card(Rank rank = Rank::ACE, Suit suit = Suit::CLUBS,
                      bool isFaceUp = true);
        inline void flip() noexcept { isFaceUp_ = !isFaceUp_; }
        inline auto getRank() const noexcept { return rank_; }
        inline auto getSuit() const noexcept { return suit_; }
        inline auto isFaceUp() const noexcept { return isFaceUp_; }
        int getValue() const noexcept;
        std::string toString() const noexcept;
    private:
        Rank rank_;
        Suit suit_;
        bool isFaceUp_;
    };
}

