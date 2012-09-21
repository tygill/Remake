#pragma once

#include "gf/Globals.h"
#include "gf/OrderedSet.h"
#include "gf/PtrHashMap.h"
#include "gf/EntityIds.h"
#include "gf/EntitySystems.h"

namespace gf {

    // The node class used by this tree is included in these same files.
    class ComponentTreeNode;

    class ComponentTree
    {
    public:
        ComponentTree();
        ~ComponentTree();

        // Entity retreval
        EntityIds getEntities(ComponentType type) const;
        EntityIds getEntities(const ComponentTypes& types) const;

        // Tells the tree to cache these sets of component types
        void registerEntityCache(ComponentType type);
        void registerEntityCache(const ComponentTypes& types);
    
        // Component caching management
        void addEntity(EntityId entId);
        void addComponent(EntityId entId, ComponentType type);
        void removeComponent(EntityId entId, ComponentType type);
        //void cacheComponents(EntityId entId);
        void removeEntity(EntityId entId);
        
        //void registerSystem(EntitySystem* system, ComponentType type);
        //void registerSystem(EntitySystem* system, const ComponentTypes& types);

    private:
        // Convenience typedef to make things easier to read
        typedef ComponentTreeNode Node;

        // For each of these internal versions of the tree modification methods, the complete component type set for the entity is needed.
        // As the EntityManager doesn't need to care about this piece of data, that will instead be included as metadata in the tree class itself.
        // It will be updated and maintained without extra effort, as the tree is alerted whenever an entity has a component added or removed.
        void addComponent(EntityId entId, ComponentType type, const ComponentTypes& types, Node* node);
        void cascadeAddComponent(EntityId entId, ComponentType type, const ComponentTypes& types, Node* node);
        void removeComponent(EntityId entId, ComponentType type, const ComponentTypes& types, Node* node);
        void cascadeRemoveComponent(EntityId entId, ComponentType type, const ComponentTypes& types, Node* node);
        //void cacheComponents(EntityId entId, ComponentTypes& types, Node* node);
        void removeEntity(EntityId entId, Node* node);

    private:
        boost::scoped_ptr<Node> root;
        HashMap<EntityId, ComponentTypes> componentTypesByEntity;
    };

    class ComponentTreeNode
    {
    public:
        ComponentTreeNode();
        ComponentTreeNode(const ComponentTypes& types);
        ~ComponentTreeNode();
    
        // Entity cache access
        void addEntity(EntityId entId);
        bool hasEntity(EntityId entId) const;
        bool removeEntity(EntityId entId);
        EntityIds getEntities() const;
        
        // System callback access (systems are called internally when entities are added or removed)
        //void addSystem(EntitySystem* system);
        //void removeSystem(EntitySystem* system);
        
        // Next node access
        // This includes the system of adding an empty node when the deepest part of the tree is reached
        ComponentTreeNode getNext(ComponentType type, bool allowCreate = false);

    private:
        friend class ComponentTree;
        typedef PtrHashMap<ComponentType, ComponentTreeNode> NextNodes;

    private:
        NextNodes getChildren() const;

    private:
        ComponentTypes types;
        EntityIds entities;
        EntitySystems callbacks;
        NextNodes nextNodes;
    };

}
