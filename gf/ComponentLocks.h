#pragma once
#include <iterator>
#include <set>

#include "gf/Globals.h"
#include "gf/ComponentLock.h"
#include "gf/HashSet.h"

namespace gf {

    class ComponentLocks
    {
    public:
        ComponentLocks();
        // T should be an iterator over ComponentType objects
        //template<class T> ComponentLocks(T uniqueBegin, T uniqueEnd, bool lockNow = true);
        //template<class T> ComponentLocks(T uniqueBegin, T uniqueEnd, T sharedBegin, T sharedEnd, bool lockNow = true);
        ComponentLocks(ComponentTypes unique, bool lockNow = true);
        ComponentLocks(ComponentTypes unique, ComponentTypes shared, bool lockNow = true);
        ~ComponentLocks();

        void lock();
        void unlock();
        bool locked() const;

    private:
        void init(std::set<ComponentType> unique, std::set<ComponentType> shared);

    private:
        HashSet<ComponentLock> locks;
    };

    template<class T> ComponentLocks::ComponentLocks(T uniqueBegin, T uniqueEnd, bool lockNow = true)
        : ComponentLocks(std::set<ComponentType>(uniqueBegin, uniqueEnd), lockNow) {}

    template<class T> ComponentLocks::ComponentLocks(T uniqueBegin, T uniqueEnd, T sharedBegin, T sharedEnd, bool lockNow = true)
        : ComponentLocks(std::set<ComponentType>(uniqueBegin, uniqueEnd), std::set<ComponentType>(sharedBegin, sharedEnd), lockNow) {}

}