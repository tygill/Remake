#include "gf/ComponentLocks.h"

namespace gf {

    ComponentLocks::ComponentLocks(ComponentTypes unique = ComponentTypes(), bool lockNow = true)
        : isLocked(false)
    {
        init(unique, ComponentTypes(), lockNow);
    }
    
    ComponentLocks::ComponentLocks(ComponentTypes unique, ComponentTypes shared, bool lockNow = true)
        : isLocked(false)
    {
        init(unique, shared, lockNow);
    }

    ComponentLocks::~ComponentLocks()
    {
    }

    void ComponentLocks::lock() {
        // Iterating over all locks MUST be done in increasing order (enforced by using an PtrOrderedMap, which orders by ComponentType)
        // This will prevent deadlock that would otherwise be caused by two sets of locks attempting to lock the same thing in different orders.
        locks.reset();
        while (locks.moveNext()) {
            locks.currentValue().lock();
        }
        isLocked = true;
    }

    void ComponentLocks::unlock() {
        locks.reset();
        while (locks.moveNext()) {
            locks.currentValue().unlock();
        }
        isLocked = false;
    }

    bool ComponentLocks::locked() const {
        return isLocked;
    }

    void ComponentLocks::init(ComponentTypes unique, ComponentTypes shared, bool lockNow) {
        unique.reset();
        while (unique.moveNext()) {
            locks.add(unique.current(), new ComponentLock(unique.current(), lockNow, true));
        }

        shared.reset();
        while (shared.moveNext()) {
            locks.add(shared.current(), new ComponentLock(shared.current(), lockNow, true));
        }

        if (lockNow) {
            lock();
        }
    }

}
