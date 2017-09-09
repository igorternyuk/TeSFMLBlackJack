#pragma once

#include "card.h"
#include <vector>
#include <string>
#include <memory>

namespace iat_bj
{
    class Hand
    {
    public:
        explicit Hand();
        ~Hand();
        Hand(const Hand&) = delete;
        Hand& operator=(const Hand&) = delete;
        Hand(Hand&&) = delete;
        Hand& operator=(Hand&&) = delete;
        void add(std::unique_ptr<Card> &upCard);
        void clear();
        int total() const;
        inline auto bustedLimit() const noexcept { return NO_BUSTED_LIMIT; }
        inline auto numCards() const noexcept { return m_cards.size(); }
        void flipFistCard();
        const std::vector<std::unique_ptr<Card>>& cards() { return m_cards; }
        std::string textDescription() const;
    private:
        enum { NUM_CARDS_MAX = 5, NO_BUSTED_LIMIT = 21 };
        std::vector<std::unique_ptr<Card>> m_cards;
    };
}


