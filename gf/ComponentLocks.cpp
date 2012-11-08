#include "gf/ComponentLocks.h"

namespace gf {

    ComponentLocks::ComponentLocks(ComponentTypes unique, bool lockNow)
        : isLocked(false)
    {
        init(unique, ComponentTypes(), lockNow);
    }
    
    ComponentLocks::ComponentLocks(ComponentTypes unique, ComponentTypes shared, bool lockNow)
        : isLocked(false)
    {
        init(unique, shared, lockNow);
    }

    ComponentLocks::ComponentLocks(const ComponentLocks& other)
        : locks(other.locks), isLocked(other.isLocked) {}

    ComponentLocks::~ComponentLocks()
    {
    }

    ComponentLocks& ComponentLocks::operator=(const ComponentLocks& other) {
        locks = other.locks;
        isLocked = other.isLocked;
        return *this;
    }

    void ComponentLocks::lock() {
        // Iterating over all locks MUST be done in increasing order (enforced by using an PtrOrderedMap, which orders by ComponentType)
        // This will prevent deadlock that would otherwise be caused by two sets of locks attempting to lock the same thing in different orders.
        Enumerator itr = locks.enumerator();
        while (itr.moveNext()) {
            itr.currentValue().lock();
        }
        isLocked = true;
    }

    void ComponentLocks::unlock() {
        Enumerator itr = locks.enumerator();
        while (itr.moveNext()) {
            itr.currentValue().unlock();
        }
        isLocked = false;
    }

    bool ComponentLocks::locked() const {
        return isLocked;
    }

    void ComponentLocks::init(ComponentTypes unique, ComponentTypes shared, bool lockNow) {
        ComponentTypes::Enumerator itr = unique.enumerator();
        while (itr.moveNext()) {
            locks.add(itr.current(), new ComponentLock(itr.current(), lockNow, true));
        }

        itr = shared.enumerator();
        while (itr.moveNext()) {
            locks.add(itr.current(), new ComponentLock(itr.current(), lockNow, true));
        }

        if (lockNow) {
            lock();
        }
    }

}
