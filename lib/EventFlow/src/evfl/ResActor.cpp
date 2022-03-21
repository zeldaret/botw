#include <algorithm>
#include <evfl/ResActor.h>
#include <ore/ResEndian.h>
#include <ore/ResMetaData.h>

namespace evfl {

void ActorBinding::Register(const ResAction* action) {
    if (GetAction(*action->name.Get()) != m_actions.end())
        return;

    Action entry;
    entry.res_action = action;
    m_actions.emplace_back(entry);
}

void ActorBinding::Register(const ResQuery* query) {
    if (GetQuery(*query->name.Get()) != m_queries.end())
        return;

    Query entry;
    entry.res_query = query;
    m_queries.emplace_back(entry);
}

ActorBinding::Action* ActorBinding::GetAction(const ore::StringView& name) {
    return std::find_if(m_actions.begin(), m_actions.end(), [name](const Action& action) {
        return name == *action.res_action->name.Get();
    });
}

const ActorBinding::Action* ActorBinding::GetAction(const ore::StringView& name) const {
    return std::find_if(m_actions.begin(), m_actions.end(), [name](const Action& action) {
        return name == *action.res_action->name.Get();
    });
}

ActorBinding::Query* ActorBinding::GetQuery(const ore::StringView& name) {
    return std::find_if(m_queries.begin(), m_queries.end(), [name](const Query& query) {
        return name == *query.res_query->name.Get();
    });
}

const ActorBinding::Query* ActorBinding::GetQuery(const ore::StringView& name) const {
    return std::find_if(m_queries.begin(), m_queries.end(), [name](const Query& query) {
        return name == *query.res_query->name.Get();
    });
}

bool ActBinder::Builder::Build(evfl::ActBinder* binder, ore::Allocator* allocator,
                               ore::IterRange<const ResActor*> actors) {
    binder->m_event_used_actor_count = 0;
    binder->m_allocator = allocator;
    binder->m_bindings.ConstructElements(actors.size(), allocator);

    auto it = actors.begin();
    for (int i = 0; i < actors.size(); ++i) {
        auto& binding = binder->m_bindings[i];
        binding.m_actor = it;
        binding.m_actions.Init(binder->m_allocator);
        binding.m_queries.Init(binder->m_allocator);
        ++it;
    }

    return true;
}

const ore::Array<ActorBinding>* ActBinder::GetUsedResActors() const {
    return &m_bindings;
}

void SwapEndian(ore::ResEndian* endian, ResActor* actor) {
    using ore::SwapEndian;
    if (endian->is_serializing) {
        if (auto* params = actor->params.ToPtr(endian->base))
            SwapEndian(endian, params);
        SwapEndian(&actor->num_actions);
        SwapEndian(&actor->num_queries);
        SwapEndian(&actor->entry_point_idx);
    } else {
        SwapEndian(&actor->num_actions);
        SwapEndian(&actor->num_queries);
        SwapEndian(&actor->entry_point_idx);
        if (auto* params = actor->params.ToPtr(endian->base))
            SwapEndian(endian, params);
    }
}

}  // namespace evfl
