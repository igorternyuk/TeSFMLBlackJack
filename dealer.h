#pragma once

#include "abstractplayer.h"

namespace iat_bj
{
    class Dealer: public AbstractPlayer
    {
    public:
        explicit Dealer(const std::string &name);
        ~Dealer();
        Dealer(const Dealer&) = delete;
        Dealer& operator=(const Dealer&) = delete;
        Dealer(Dealer&&) = delete;
        Dealer& operator=(Dealer&&) = delete;
        inline void flipFirstCard() { m_hand->flipFistCard(); }
        bool virtual isHitting() const;
        virtual std::string getHandTextDescription() const override;
        inline auto getCasinoBalance() { return m_casinoBank; }
        inline void payToWinner(double money) { m_casinoBank -= money; }
        inline void takeLosersBet(double money) { m_casinoBank += money; }
    private:
        enum { HITTING_LIMIT = 16 };
        double m_casinoBank{0};
    };
}


