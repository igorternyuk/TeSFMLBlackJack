#pragma once
#include "abstractplayer.h"
#include <vector>
#include <memory>

namespace iat_bj
{
    class Card;

    class Deck
    {
    public:
        explicit Deck();
        ~Deck();
        Deck(const Deck&) = delete;
        Deck& operator=(const Deck&) = delete;
        Deck(Deck&&) = delete;
        Deck& operator=(Deck&&) = delete;
        void populate();
        void shuffle();
        void deal(AbstractPlayer &player);
    private:
        enum { NUM_CARDS = 52};
        std::vector<std::unique_ptr<Card>> m_cards;
    };
}


