#pragma once

#include "gf/Globals.h"
#include "gf/HashMap.h"
#include "gf/Component.h"
#include "gf/ComponentTree.h"
#include "gf/ComponentPtr.h"
#include "gf/Entity.h"
#include "gf/Entities.h"

namespace gf {

    class EntityManager
    {
    public:
        EntityManager();
        ~EntityManager();

        EntityId create();
        //EntityId create(EntityTemplate* temp);
    
        bool exists(EntityId entId) const;
        bool destroy(EntityId entId);

        ComponentTypes componentTypes(EntityId entId) const;
    
        template<class T> ComponentPtr<T> addComponent(EntityId entId);
        template<class T> bool hasComponent(EntityId entId) const;
        bool hasComponent(ComponentType type, EntityId entId) const;
        template<class T> ComponentPtr<T> getComponent(EntityId entId) const;
        ComponentPtr<Component> getComponent(ComponentType type, EntityId entId) const;
        template<class T> bool removeComponent(EntityId entId);
        bool removeComponent(ComponentType type, EntityId entId);
    
        Entity entity(EntityId entId) const;
    
        /* T extends Component */
        template<class T> Entities getEntities() const;
        Entities getEntities(ComponentType type) const;
        Entities getEntities(const ComponentTypes& types) const;
    
        // One of these functions must be called before getEntities() will return the set of entities with these components.
        // Also note that this must be called at initialization time, before any entities have been created.
        template<class T> void registerEntityCache();
        void registerEntityCache(ComponentType type);
        void registerEntityCache(const ComponentTypes& types);

        void registerSystem(EntitySystem* system, ComponentType type);
        void registerSystem(EntitySystem* system, const ComponentTypes& types);

    private:
        // typedef to pretty up the entities map
        typedef HashMap<ComponentType, boost::shared_ptr<Component> > InternalEntity;

    private:
        HashMap<EntityId, InternalEntity> entities;
        ComponentTree componentTree;
    };

}
