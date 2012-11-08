#include "gf/ComponentLock.h"

namespace gf {

    PtrHashMap<ComponentType, boost::shared_mutex> ComponentLock::componentMutexes;

    ComponentLock::ComponentLock(ComponentType t, bool lockNow, bool isUniqueLock)
        : type(t), useUniqueLock(isUniqueLock)
    {
        if (lockNow) {
            lock();
        }
    }

    ComponentLock::ComponentLock(const ComponentLock& other)
        : sharedLock(other.sharedLock), uniqueLock(other.uniqueLock), type(other.type), useUniqueLock(other.useUniqueLock) {}

    ComponentLock::~ComponentLock()
    {
        // Unlocking is implicit with the smart pointers
    }
    
    ComponentLock& ComponentLock::operator=(const ComponentLock& other) {
        sharedLock = other.sharedLock;
        uniqueLock = other.uniqueLock;
        type = other.type;
        useUniqueLock = other.useUniqueLock;
        return *this;
    }

    void ComponentLock::lock() {
        // Make sure the other type of lock isn't set
        unlock();
        if (useUniqueLock) {
            uniqueLock.swap(boost::shared_ptr<boost::unique_lock<boost::shared_mutex> >(new boost::unique_lock<boost::shared_mutex>(componentMutexes.get(type))));
        } else {
            sharedLock.swap(boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(new boost::shared_lock<boost::shared_mutex>(componentMutexes.get(type))));
        }
    }

    void ComponentLock::unlock() {
        uniqueLock.reset();
        sharedLock.reset();
    }

    bool ComponentLock::locked() const {
        return uniqueLock || sharedLock;
    }

    bool ComponentLock::unique() const {
        return useUniqueLock;
    }

    bool ComponentLock::operator<(const ComponentLock& other) const {
        return type < other.type;
    }

    ComponentType ComponentLock::componentType() const {
        return type;
    }

    void ComponentLock::registerComponentType(ComponentType type) {
        componentMutexes.add(type, new boost::shared_mutex());
    }
}
