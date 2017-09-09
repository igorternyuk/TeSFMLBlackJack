#pragma once

#include "player.h"
#include "dealer.h"
#include <memory>

namespace iat_bj
{
    class ConstantModelInterface
    {
    public:
        virtual ~ConstantModelInterface() {}
        virtual int numPlayers() const noexcept = 0;
        virtual int numRounds() const noexcept = 0;
        virtual const std::vector<std::unique_ptr<Player>>& players() const noexcept = 0;
        virtual const std::unique_ptr<Dealer>& dealer() const noexcept = 0;
    };
}


