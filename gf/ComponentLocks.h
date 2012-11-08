#pragma once
#include <iterator>
#include <set>

#include "gf/Globals.h"
#include "gf/ComponentLock.h"
#include "gf/HashSet.h"
#include "gf/ComponentTypes.h"
#include "gf/PtrOrderedMap.h"

namespace gf {

    class ComponentLocks
    {
    public:
        ComponentLocks(ComponentTypes unique, bool lockNow = true);
        ComponentLocks(ComponentTypes unique, ComponentTypes shared, bool lockNow = true);
        ComponentLocks(const ComponentLocks& other);
        ~ComponentLocks();

        ComponentLocks& operator=(const ComponentLocks& other);

        void lock();
        void unlock();
        bool locked() const;

    private:
        typedef PtrOrderedMap<ComponentType, ComponentLock>::Enumerator Enumerator;

    private:
        void init(ComponentTypes unique, ComponentTypes shared, bool lockNow);

    private:
        PtrOrderedMap<ComponentType, ComponentLock> locks;
        bool isLocked;

    };

}