#pragma once

#include <evfl/ResActor.h>

namespace sead {
class Heap;
}

namespace ksys::evt {
class ActorBinding;
class ActorBindings;
}  // namespace ksys::evt

namespace ksys::res {

class EventFlowBinder {
public:
    EventFlowBinder(evt::ActorBindings* bindings, sead::Heap* heap)
        : mBindings(bindings), mHeap(heap) {}
    virtual ~EventFlowBinder() = default;
    EventFlowBinder(const EventFlowBinder&) = default;
    EventFlowBinder& operator=(const EventFlowBinder&) = default;

protected:
    evt::ActorBindings* mBindings;
    sead::Heap* mHeap;
};

class EventFlowActorBinder : public EventFlowBinder {
public:
    using EventFlowBinder::EventFlowBinder;
    void bind(evfl::ActorBinding* evfl_binding, const evfl::ResActor* evfl_actor);
};

class EventFlowActionBinder : public EventFlowBinder {
public:
    using EventFlowBinder::EventFlowBinder;
    void bind(evfl::ActorBinding::Action* evfl_binding, const evfl::ResAction* evfl_action,
              const evfl::ResActor* evfl_actor, evt::ActorBinding* binding);
};

class EventFlowQueryBinder : public EventFlowBinder {
public:
    using EventFlowBinder::EventFlowBinder;
    void bind(evfl::ActorBinding::Query* evfl_binding, const evfl::ResQuery* evfl_query,
              const evfl::ResActor* evfl_actor, evt::ActorBinding* binding);
};

}  // namespace ksys::res
