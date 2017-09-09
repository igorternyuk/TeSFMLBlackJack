#pragma once
#include "abstractplayer.h"

namespace iat_bj
{
    class Player: public AbstractPlayer
    {
    public:
        enum class Status {HITTING, STAND, WON, LOST, PUSH};
        enum class Type {HUMAN, BOT};
        explicit Player(const std::string &name, double money, Type type = Type::BOT);
        ~Player();
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        Player(Player&&) = delete;
        Player& operator=(Player&&) = delete;
        inline void setStatus(Status newStatus) { m_status = newStatus; }
        inline auto getStatus() const noexcept { return m_status; }
        inline auto getMoneyBalance() const noexcept { return m_money; }
        inline auto getBetValue() const noexcept { return m_bet; }
        virtual std::string getHandTextDescription() const override;
        virtual bool isHitting() const;
        //money stuff
        inline void bet() { m_money -= m_bet; }
        inline void award(double coefficient) { m_money += (coefficient + 1) * m_bet; }
        inline void addBonus(int bonus) { m_money += bonus; }
        inline void giveBetBack() { m_money += m_bet; } // In the case of push
    private:
        double m_money;
        Type m_type;
        Status m_status{Status::HITTING};
        double m_bet{m_money / 10};
        int m_limit{0};
    };
}


