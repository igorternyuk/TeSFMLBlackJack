#pragma once

#include "deck.h"
#include "modellistener.h"
#include "constantmodelinterface.h"

#include <list>
#include <vector>
#include <string>

namespace iat_bj
{
    class Model: public ConstantModelInterface
    {
    public:
        explicit Model();
        ~Model();
        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;
        Model(Model&&) = delete;
        Model& operator=(Model&&) = delete;
        //Constant interface for view
        inline int numPlayers() const noexcept { return NUM_PLAYERS; }
        inline int numRounds() const noexcept { return m_numRounds; }
        inline const std::vector<std::unique_ptr<Player>>& players() const noexcept
        { return m_players; }
        inline const std::unique_ptr<Dealer>& dealer() const noexcept
        { return m_dealer; }
        //Interface for controller
        void startNewRound();
        void hit();
        void stand();
        void addListener(std::shared_ptr<ModelListener> spListener);
        void removeListener(std::shared_ptr<ModelListener> spListener);
    private:
        enum
        {
            NUM_PLAYERS = 5,
            NUM_CARDS_INIT = 2,
            INIT_PLAYER_MONEY = 1000,
            BONUS777 = 500,
            BONUS_BLACKJACK_SAME_SUIT = 300
        };
        const double COEF_WIN_TWO_ACES {2.0};
        const double COEF_WIN_BLACK_JACK {1.5};
        const double COEF_WIN {1.0};
        std::unique_ptr<Deck> m_deck;
        std::unique_ptr<Dealer> m_dealer;
        std::vector<std::unique_ptr<Player>> m_players;
        int m_numRounds{0};
        std::list<std::weak_ptr<ModelListener>> m_listeners;
        void checkWinners();
        void dealToBotsAndDealer();
        void awardWinner(Player &p);
        void notifyAllListeners();
    };
}

