#include "player.h"
#include "random.h"
#include "utils.h"
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Player::Player(const std::string &name, double money, Type type):
    AbstractPlayer{name}, m_money{money}, m_type{type}
{
    if(m_type == Type::HUMAN)
    {
        m_limit = m_hand->bustedLimit();
    }
    else
    {
        Random r;
        m_limit = r.nextInt(14,18);
    }
}

iat_bj::Player::~Player()
{
#ifdef DEBUG
    std::cout << "Player destructor was called" << std::endl;
#endif
}

std::string iat_bj::Player::getHandTextDescription() const
{
    std::string status;
    switch(m_status)
    {
        case Status::HITTING:
            status = "\nHitting";
            break;
        case Status::STAND:
            status = "\nStand";
            break;
        case Status::WON:
            status = "\nWON!!!";
            break;
        case Status::LOST:
            status = "\nLOST!";
            break;
        case Status::PUSH:
            status = "\nPush!";
            break;
    }

    return AbstractPlayer::getHandTextDescription() + status +
           std::string("-Balance:") + convertToStringWithPrecision(m_money,1) +
           std::string("$");
}


bool iat_bj::Player::isHitting() const
{
    return m_hand->total() < m_limit;
}
