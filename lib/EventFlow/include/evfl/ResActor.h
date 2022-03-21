#pragma once

#include <cstddef>
#include <ore/Array.h>
#include <ore/BinaryFile.h>
#include <ore/IterRange.h>
#include <utility>

namespace ore {
struct ResEndian;
struct ResMetaData;
}  // namespace ore

namespace evfl {

struct ActionArg;
class ActionDoneHandler;
class FlowchartContext;
class FlowchartContextNode;
class FlowchartObj;
struct QueryArg;

struct ResAction {
    ore::BinTPtr<ore::BinString> name;
};

struct ResQuery {
    ore::BinTPtr<ore::BinString> name;
};

struct ResActor {
    bool HasArgumentName() const { return !argument_name.Get()->empty(); }

    ore::BinTPtr<ore::BinString> name;
    ore::BinTPtr<ore::BinString> secondary_name;
    ore::BinTPtr<ore::BinString> argument_name;
    ore::BinTPtr<ResAction> actions;
    ore::BinTPtr<ResQuery> queries;
    ore::BinTPtr<ore::ResMetaData> params;
    u16 num_actions;
    u16 num_queries;
    /// Entry point index for assicated entry point (0xffff if none)
    u16 entry_point_idx;
    // TODO: Cut number? This is set to 1 for flowcharts but other values have been seen
    // for timeline actors.
    u8 cut_number;
};

using ActionHandler = void (*)(const ActionArg& arg, ActionDoneHandler done_handler);
using QueryHandler = int (*)(const QueryArg& arg);

class ActorBinding {
public:
    struct Action {
        ActionHandler handler{};
        void* user_data{};
        const ResAction* res_action{};
    };

    struct Query {
        QueryHandler handler{};
        void* user_data{};
        const ResQuery* res_query{};
    };

    ActorBinding() = default;

    void Register(const ResAction* action);
    void Register(const ResQuery* query);

    // Similar to std::find_if. Returns m_actions.end() if the specified action is not found.
    Action* GetAction(const ore::StringView& name);
    const Action* GetAction(const ore::StringView& name) const;
    Query* GetQuery(const ore::StringView& name);
    const Query* GetQuery(const ore::StringView& name) const;

    ore::DynArrayList<Action>& GetActions() { return m_actions; }
    ore::DynArrayList<Query>& GetQueries() { return m_queries; }
    const ore::DynArrayList<Action>& GetActions() const { return m_actions; }
    const ore::DynArrayList<Query>& GetQueries() const { return m_queries; }
    auto ActionsEnd() const { return m_actions.end(); }
    auto QueriesEnd() const { return m_queries.end(); }

    auto GetActor() const { return m_actor; }

    void* GetUserData() const { return m_user_data; }
    void SetUserData(void* user_data) { m_user_data = user_data; }

    bool IsInitialized() const { return m_initialized; }
    bool IsUsed() const { return m_is_used; }
    void SetInitialized(bool initialized) { m_initialized = initialized; }
    void SetIsUsed(bool used) { m_is_used = used; }

    void UnbindAll() {
        m_user_data = nullptr;
        m_initialized = false;
        for (auto it = m_actions.begin(); it != m_actions.end(); ++it) {
            it->handler = nullptr;
            it->user_data = nullptr;
        }
        for (auto it = m_queries.begin(); it != m_queries.end(); ++it) {
            it->handler = nullptr;
            it->user_data = nullptr;
        }
    }

private:
    friend class ActBinder;

    ore::DynArrayList<Action> m_actions{};
    ore::DynArrayList<Query> m_queries{};
    void* m_user_data{};
    const ResActor* m_actor{};
    bool m_initialized{};
    bool m_is_used{};
};

class ActBinder {
public:
    class Builder {
    public:
        bool Build(evfl::ActBinder* binder, ore::Allocator* allocator,
                   ore::IterRange<const ResActor*> actors);
    };

    ActBinder() = default;
    ActBinder(const ActBinder&) = delete;
    auto operator=(const ActBinder&) = delete;

#ifdef MATCHING_HACK_NX_CLANG
    [[gnu::always_inline]]
#endif
    ~ActBinder() {
        Reset();
    }

    u32 GetEventUsedActorCount() const { return m_event_used_actor_count; }
    const ore::Array<ActorBinding>* GetUsedResActors() const;

    ore::Array<ActorBinding>& GetBindings() { return m_bindings; }
    const ore::Array<ActorBinding>& GetBindings() const { return m_bindings; }
    void IncrementNumActors() { ++m_event_used_actor_count; }
    void SetIsUsed() { m_is_used = true; }
    bool IsUsed() const { return m_is_used; }

    void RegisterAction(int actor_idx, const evfl::ResAction* action) {
        auto& binding = GetBindings()[actor_idx];
        if (!binding.IsUsed() && binding.GetActor()->argument_name.Get()->empty()) {
            IncrementNumActors();
            binding.SetIsUsed(true);
        }
        binding.Register(action);
    }

    void RegisterQuery(int actor_idx, const evfl::ResQuery* query) {
        auto& binding = GetBindings()[actor_idx];
        if (!binding.IsUsed() && binding.GetActor()->argument_name.Get()->empty()) {
            IncrementNumActors();
            binding.SetIsUsed(true);
        }
        binding.Register(query);
    }

    void UnbindAll() {
        for (auto it = m_bindings.begin(); it != m_bindings.end(); ++it)
            it->UnbindAll();
    }

    void Reset() {
        m_event_used_actor_count = 0;
        if (auto* data = m_bindings.data()) {
            m_bindings.ClearWithoutFreeing();
            m_allocator->Free(data);
        }
        m_allocator = nullptr;
    }

private:
    u32 m_event_used_actor_count{};
    ore::Allocator* m_allocator{};
    ore::SelfDestructingArray<ActorBinding> m_bindings{};
    bool m_is_used{};
};

void SwapEndian(ore::ResEndian* endian, ResActor* actor);

}  // namespace evfl
