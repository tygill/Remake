#pragma once
#include <boost/thread.hpp>

#include "gf/Globals.h"
#include "gf/GameFrame.h"
#include "gf/EntitySystem.h"
#include "gf/EntitySystems.h"

namespace gf {

    class GameFrameThread
    {
    public:
        GameFrameThread(GameFrame* frame);
        ~GameFrameThread();

        void addSystem(EntitySystem* system);

        void operator()();

    private:
        GameFrame* framework;
        EntitySystems systems;

    };

}
