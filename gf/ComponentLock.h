#pragma once
#include <boost/thread.hpp>

#include "gf/Globals.h"
#include "gf/PtrHashMap.h"

namespace gf {

    // This class provides the standard internal interface for locking a specific ComponentType
    class ComponentLock
    {
    public:
        ComponentLock(ComponentType t, bool lockNow = true, bool isUniqueLock = true);
        //ComponentLock(const ComponentLock& other);
        ~ComponentLock();

        void lock();
        void unlock();
        bool locked() const;

        // This is to allow ComponentLocks to be stored in an ordered set, so that locks are acquired in increasing order.
        // If locks are always acquired in increasing order whenever multiple locks need to be made, deadlocks will never occur.
        bool operator<(const ComponentLock& other) const;

        // Alternatively, we could just use a lambda expression and the ComponentType
        ComponentType componentType() const;
    
    public:
        // static component type registration function
        // This should be called automatically when the component is registered.
        static void registerComponentType(ComponentType type);

    private:
        static PtrHashMap<ComponentType, boost::shared_mutex> componentMutexes;

    private:
        // Would a scoped pointer work while copying these around?
        // Safer this way, I suppose.
        boost::shared_ptr<boost::shared_lock<boost::shared_mutex> > sharedLock;
        boost::shared_ptr<boost::unique_lock<boost::shared_mutex> > uniqueLock;
        ComponentType type;
        bool useUniqueLock;
    };

}
