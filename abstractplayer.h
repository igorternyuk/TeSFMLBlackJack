#pragma once

#include "hand.h"
#include <string>
#include <memory>

namespace iat_bj {
    class Card;

    class AbstractPlayer
    {
    public:
        explicit AbstractPlayer(const std::string &name);
        virtual ~AbstractPlayer();
        inline auto getName() const noexcept { return m_name; }
        inline const std::vector<std::unique_ptr<Card>>& getCards() const { return m_hand->cards(); }
        bool isBusted() const;
        int getHandTotal() const;
        bool hasBlackJack() const;
        bool hasTwoCardWithSameSuit() const;
        bool hasTwoAces() const;
        bool hasThreeSevens() const;
        virtual std::string getHandTextDescription() const;
        //indicates whether or not abstract player wants to keep hitting
        virtual bool isHitting() const = 0;
        void addCard(std::unique_ptr<Card> &card);
        void clearCards();
    protected:
        enum { BUSTED_LIMIT = 21 };
        std::string m_name;
        std::unique_ptr<Hand> m_hand;
    };
}

