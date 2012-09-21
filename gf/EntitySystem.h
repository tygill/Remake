#pragma once
#include <boost/thread.hpp>

#include "gf/Globals.h"
#include "gf/Queue.h"
#include "gf/GameFrame.h"
#include "gf/ComponentTypes.h"

namespace gf {

    class EntitySystem
    {
    public:
        EntitySystem(GameFrame* frame);
        virtual ~EntitySystem();
    
        // Initialization will occur in the new thread, so thread-specific
        // init stuff must be here and not the constructor
        virtual void init();
        virtual void destroy();
    
        // Doesn't do anything by default. This way systems can be
        // created that only do things when entities are added or removed.
        
        // These are where all the new behavior should be:
        //  update, added, removed

        // Delta is in milliseconds
        virtual void update(int deltaMsec);
        
        // Callbacks - must be reentrant and threadsafe
        // Called by the EntityManager after the system has been registered
        // As they may be queued by id, these should make sure that the entity still exists, and
        // still has the components that this system cares about. If the components were removed,
        // or the entity was destroyed before the added event is triggered, accessors could return
        // null pointers.
        virtual void added(EntityId entity);
        virtual void removed(EntityId entity);
        
        // This needs to be threadsafely callable from any other thread that could fire the event
        virtual void receive(MessagePtr<Message const> message);
        
        // These are the threadsafe callbacks that will be called automatically by the framework.
        // Custom implementations should reside in the functions above, as these will call those
        // once things are threadsafe.
        void threadsafeUpdate(int deltaMsec);
        // For these two methodes, the type set is used to lock those types when the added function
        // is called. As EntityIds are passed rather than pointers, these types will be locked only
        // when the actual added() function is being called.
        // This way, the component types locked by types are not locked the entire time entity is in
        // the queue.
        void threadsafeAdded(EntityId entity, const ComponentTypes& types);
        void threadsafeRemoved(EntityId entity, const ComponentTypes& types);
        void threadsafeReceive(MessagePtr<Message const> message);
        
    protected:
        GameFrame* framework() const;

    private:
        typedef std::pair<EntityId, ComponentTypes> EntityQueueNode;
        typedef Queue<EntityQueueNode> EntityQueue;
        typedef Queue<MessagePtr<Message> > MessageQueue;

    private:
        GameFrame* gameFrame;
    
        boost::mutex updateMutex;
        boost::mutex messageMutex;
        boost::mutex addedMutex;
        boost::mutex removedMutex;

        EntityQueue addedQueue;
        EntityQueue removedQueue;

        MessageQueue messageQueue;

        // This function should ONLY be called when the updateMutex is already owned by the thread.
        // Unless some thing drastic changes, it should ONLY be called at the end of the threadsafeUpdate
        // function.
        void processQueues();

    };

}
