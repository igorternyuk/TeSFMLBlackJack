#include "dealer.h"
#include "utils.h"
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Dealer::Dealer(const std::string &name):
    AbstractPlayer(name)
{}

iat_bj::Dealer::~Dealer()
{
#ifdef DEBUG
   std::cout << "Dealer destructor was called" << std::endl;
#endif
}


bool iat_bj::Dealer::isHitting() const
{
    return m_hand->total() <= HITTING_LIMIT;
}

std::string iat_bj::Dealer::getHandTextDescription() const
{
    return AbstractPlayer::getHandTextDescription() +
           std::string("\nCasino balance:") +
           convertToStringWithPrecision(m_casinoBank,1) +
           std::string("$");
}
