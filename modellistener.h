#pragma once

namespace iat_bj
{
    class ModelListener
    {
    public:
        virtual ~ModelListener() {}
        virtual void updateView() = 0;
    };
}

