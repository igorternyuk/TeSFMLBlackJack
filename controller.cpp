#include "controller.h"
#include "model.h"
#ifdef DEBUG
#include <iostream>
#endif

iat_bj::Controller::Controller(std::shared_ptr<Model> spModel):
    m_spModel{spModel}
{}

iat_bj::Controller::~Controller()
{
#ifdef DEBUG
   std::cout << "Controller destructor was called" << std::endl;
#endif
}

void iat_bj::Controller::startNewRound()
{
    m_spModel->startNewRound();
}

void iat_bj::Controller::sayHitMe()
{
    m_spModel->hit();
}

void iat_bj::Controller::sayStand()
{
    m_spModel->stand();
}
