#pragma once
#include <memory>

namespace iat_bj
{
    class Model;
    class Controller
    {
    public:
        Controller(std::shared_ptr<Model> spModel);
        ~Controller();
        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;
        Controller(Controller&&) = delete;
        Controller& operator=(Controller&&) = delete;
        void startNewRound();
        void sayHitMe();
        void sayStand();
    private:
        std::shared_ptr<Model> m_spModel;
    };
}


