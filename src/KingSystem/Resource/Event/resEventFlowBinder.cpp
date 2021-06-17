#include "KingSystem/Resource/Event/resEventFlowBinder.h"
#include "KingSystem/Event/evtActorBinding.h"
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtActorManager.h"

namespace ksys::res {

void EventFlowActorBinder::bind(evfl::ActorBinding* evfl_binding,
                                const evfl::ResActor* evfl_actor) {
    auto* binding = mBindings->bindActor(evfl_actor, mHeap);
    if (binding) {
        evfl_binding->SetUserData(binding);
        evfl_binding->SetInitialized(true);
    }
}

void EventFlowActionBinder::bind(evfl::ActorBinding::Action* evfl_binding,
                                 const evfl::ResAction* evfl_action,
                                 const evfl::ResActor* evfl_actor, evt::ActorBinding* binding) {
    if (binding)
        binding->bindAction(evfl_action);

    evfl_binding->handler = evt::ActorManager::actionHandler;
    evfl_binding->user_data = nullptr;
}

void EventFlowQueryBinder::bind(evfl::ActorBinding::Query* evfl_binding,
                                const evfl::ResQuery* evfl_query, const evfl::ResActor* evfl_actor,
                                evt::ActorBinding* binding) {
    if (binding)
        binding->bindQuery(evfl_query);

    evfl_binding->handler = evt::ActorManager::queryHandler;
    evfl_binding->user_data = nullptr;
}

}  // namespace ksys::res
