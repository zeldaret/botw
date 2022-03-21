#pragma once

#include <evfl/EvflAllocator.h>
#include <evfl/ResActor.h>
#include <ore/Array.h>
#include <ore/Buffer.h>
#include <ore/EnumUtil.h>
#include <ore/IntrusiveList.h>
#include <ore/IterRange.h>
#include <ore/StringView.h>
#include <ore/Types.h>

namespace ore {
class Allocator;
class BitArray;
}  // namespace ore

namespace evfl {

class MetaDataPack;
struct ResEntryPoint;
struct ResEvent;
struct ResFlowchart;
class VariablePack;

ORE_ENUM(SubFlowCallbackType, kEnter, kLeave)

class FlowchartObj {
public:
    class Builder {
    public:
        Builder(const ResFlowchart* flowchart, ore::BitArray* visited_entry_points)
            : m_flowchart(flowchart), m_entry_points_mask(visited_entry_points) {}

        bool Build(FlowchartObj* obj, ore::Allocator* allocator,
                   ore::IterRange<const ResFlowchart* const*> flowcharts);

    private:
        const ResFlowchart* m_flowchart{};
        ore::BitArray* m_entry_points_mask{};
        ActBinder::Builder m_act_binder_builder{};
    };

#ifdef MATCHING_HACK_NX_CLANG
    [[gnu::always_inline]]
#endif
    ~FlowchartObj() = default;

    const ResFlowchart* GetFlowchart() const { return m_flowchart; }
    const ActBinder& GetActBinder() const { return m_act_binder; }
    ActBinder& GetActBinder() { return m_act_binder; }

private:
    const ResFlowchart* m_flowchart{};
    ActBinder m_act_binder;
};

class FlowchartContextNode {
public:
    ORE_ENUM(State, kInvalid, kFree, kNotInvoked, kInvoked, kDone, kWaiting)

    FlowchartContextNode() { Reset(); }

    bool IsInvalidOrFree() const { return m_state == State::kInvalid || m_state == State::kFree; }
    FlowchartObj* GetObj() const { return m_obj; }
    VariablePack* GetVariablePack() const { return m_variable_pack; }
    int GetNodeCounter() const { return m_node_counter; }
    u16 GetEventIdx() const { return m_event_idx; }
    u16 GetNextNodeIdx() const { return m_next_node_idx; }
    State::Type GetState() const { return m_state; }

    void Reset() {
        m_node_counter = -1;
        m_obj = nullptr;
        m_event_idx = -1;
        m_next_node_idx = -1;
        m_idx = -1;
        m_state = State::kInvalid;
        m_variable_pack = nullptr;
        m_owns_variable_pack = false;
    }

private:
    friend class ActionDoneHandler;
    friend class FlowchartContext;

    FlowchartObj* m_obj;
    VariablePack* m_variable_pack;
    int m_node_counter;
    u16 m_event_idx;
    u16 m_next_node_idx;
    u16 m_idx;
    ore::SizedEnum<State::Type, u8> m_state;
    bool m_owns_variable_pack;
};

class FlowchartContext {
public:
    class Builder {
    public:
        using FlowchartRange = ore::IterRange<const ResFlowchart* const*>;
        ORE_ENUM(BuildResultType, kSuccess, kInvalidOperation, kResFlowchartNotFound, kEntryPointNotFound)

        struct BuildResult {
            BuildResultType::Type result;
            /// Indicates which flowchart was required yet couldn't be found.
            ore::StringView missing_flowchart_name{};
            /// Indicates which entry point was required yet couldn't be found.
            ore::StringView missing_entry_point_name{};
        };

        Builder() = default;
        explicit Builder(FlowchartRange flowcharts, int flowchart_idx = 0)
            : m_flowcharts(flowcharts), m_flowchart_idx(flowchart_idx) {}

        bool SetEntryPoint(const ore::StringView& flowchart_name,
                           const ore::StringView& entry_point_name);
        bool SetEntryPoint(BuildResult* result, const ore::StringView& flowchart_name,
                           const ore::StringView& entry_point_name);

        bool Build(FlowchartContext* context, AllocateArg allocate_arg);
        bool Build(BuildResult* result, FlowchartContext* context, AllocateArg allocate_arg);

    private:
        bool BuildImpl(BuildResult* result, FlowchartRange flowcharts, FlowchartContext* context,
                       AllocateArg allocate_arg, ore::Buffer flowchart_obj_buffer);

        FlowchartRange m_flowcharts{};
        int m_flowchart_idx = 0;
        int m_entry_point_idx = -1;
    };

    FlowchartContext();
    ~FlowchartContext() {
        Dispose();
        m_objs.DestructElements();
    }

    FlowchartContext(const FlowchartContext&) = delete;
    auto operator=(const FlowchartContext&) = delete;

    void Start(MetaDataPack* pack);
    int AllocNode();
    void AllocVariablePack(FlowchartContextNode& node, const ResEntryPoint& entry_point);
    void ProcessContext();
    FlowchartObj* FindFlowchartObj(ore::StringView name);
    const FlowchartObj* FindFlowchartObj(ore::StringView name) const;
    void UnbindAll();
    void Clear();
    void FreeVariablePack(FlowchartContextNode& node);
    void CopyVariablePack(FlowchartContextNode& src, FlowchartContextNode& dst);
    bool ProcessContextNode(int node_idx);
    ActorBinding* TrackBackArgumentActor(int node_idx, const ore::StringView& name);
    bool IsUsing(const ResFlowchart* flowchart) const;
    bool IsPlaying(const ResFlowchart* flowchart) const;
    const ore::Array<ActorBinding>* GetUsedResActors(ore::StringView flowchart_name) const;

    FlowchartContextNode& GetNode(int idx) { return m_nodes[idx]; }
    const FlowchartContextNode& GetNode(int idx) const { return m_nodes[idx]; }
    MetaDataPack* GetMetaDataPack() const { return m_metadata_pack; }
    ore::Array<FlowchartObj>& GetObjs() { return m_objs; }
    const ore::Array<FlowchartObj>& GetObjs() const { return m_objs; }

private:
    void Dispose() {
        m_obj_idx = -1;
        m_active_entry_point_idx = -1;
        m_metadata_pack = nullptr;
        m_objs.Clear(&m_allocator);
        for (auto& node : m_nodes)
            FreeVariablePack(node);
        m_nodes.Reset();
    }

    void UpdateNodeCounter(int node_idx) {
        auto& node = GetNode(node_idx);
        node.m_node_counter = ++s_GlobalCounter;
    }

    void CallSubFlowCallback(const ResFlowchart* flowchart, const ResEvent* event,
                             SubFlowCallbackType::Type type) {
#ifdef EVFL_VER_LABO
        if (m_on_sub_flow_callback)
            m_on_sub_flow_callback(this, flowchart, event, type);
#endif
    }

    static int s_GlobalCounter;

    EvflAllocator m_allocator;
    ore::Array<FlowchartObj> m_objs;
    ore::DynArrayList<FlowchartContextNode> m_nodes;
    ore::IntrusiveList<ActionDoneHandler> m_handlers;
#ifdef EVFL_VER_LABO
    void (*m_on_sub_flow_callback)(FlowchartContext* context, const ResFlowchart* flowchart,
                                   const ResEvent* event, SubFlowCallbackType::Type type) = nullptr;
#endif
    MetaDataPack* m_metadata_pack = nullptr;
    void* _78 = nullptr;
    int m_next_node_idx = 0;
    int m_num_allocated_nodes = 0;
    int m_obj_idx = -1;
    int m_active_entry_point_idx = -1;
    bool m_is_processing = false;
    u8 _91 = 0;
};

}  // namespace evfl
