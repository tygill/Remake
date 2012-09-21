#pragma once

#include "gf/Globals.h"
#include "gf/EntityManager.h"
#include "gf/MessageManager.h"
#include "gf/ResourceManager.h"
#include "gf/EntitySystem.h"
#include "gf/PtrHashMultimap.h"

namespace gf {

    class GameFrame
    {
    public:
        GameFrame();
        ~GameFrame();
    
        template<class T> T* addSystem();
        template<class T> T* addSystem(int thread);
        
        // This is what actually builds the threads (0 is the main() thread)
        // It adds them all to a thread group, and then runs them until
        // they all stop. This is designed to be the return to main(), so
        // error codes can be returned as ints.
        int run();

        bool isRunning() const;
        void stop();
        
        EntityManager& entityManager();
        ResourceManager& resourceManager();
        MessageManager& messageManager();

    private:
        typedef PtrHashMultimap<int, EntitySystem> EntitySystemStorage;

    private:
        EntitySystemStorage systems;

        bool running;
        
        EntityManager entities;
        ResourceManager resources;
        MessageManager messages;
    };

}
