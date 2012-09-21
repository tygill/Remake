#pragma once

#include "gf/Globals.h"
#include "gf/EntitySystem.h"
#include "gf/OrderedSet.h"
#include "gf/HashMap.h"
#include "gf/Message.h"
#include "gf/MessagePtr.h"
#include "gf/EntitySystems.h"

namespace gf {

    class MessageManager
    {
    public:
        MessageManager();
        ~MessageManager();
        
        // Sends the defaultly instanciated version of T
        template<class T> void send();
        void send(MessagePtr<Message const> message);
        
        // Setup systems
        void registerSystem(EntitySystem* system, MessageType type);

    private:
        typedef HashMap<MessageType, EntitySystems> MessageMap;

    private:
        MessageMap messageMap;
        
    };

}
