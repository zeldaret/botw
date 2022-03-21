#include <algorithm>
#include <evfl/Action.h>
#include <evfl/Flowchart.h>
#include <evfl/Param.h>
#include <evfl/Query.h>
#include <evfl/ResFlowchart.h>
#include <iterator>
#include <ore/Array.h>
#include <ore/BitUtils.h>
#include <ore/IterRange.h>
#include <ore/ResDic.h>
#include <ore/StringView.h>

namespace evfl {

int FlowchartContext::s_GlobalCounter{};

FlowchartContext::FlowchartContext() {
    m_handlers.SetOffset(ActionDoneHandler::GetListNodeOffset());
}

void FlowchartContext::Start(MetaDataPack* pack) {
    auto& obj = m_objs[m_obj_idx];
    const auto& entry_point = obj.GetFlowchart()->entry_points.Get()[m_active_entry_point_idx];

    const auto main_event_idx = entry_point.main_event_idx;
    if (main_event_idx == 0xffff)
        return;

    m_metadata_pack = pack;

    const int node_idx = AllocNode();
    auto& node = m_nodes[node_idx];
    node.m_obj = &obj;
    node.m_event_idx = main_event_idx;
    node.m_next_node_idx = -1;
    node.m_idx = node_idx;
    node.m_state = FlowchartContextNode::State::kNotInvoked;
    AllocVariablePack(node, entry_point);

    ProcessContext();
}

int FlowchartContext::AllocNode() {
    int idx = m_next_node_idx;

    if (idx == 0xffff) {
        idx = m_nodes.size();
        m_nodes.Resize(2 * m_nodes.size());
        for (int i = idx, n = m_nodes.size(); i < n - 1; ++i) {
            m_nodes[i].m_next_node_idx = i + 1;
            m_nodes[i].m_state = FlowchartContextNode::State::kFree;
        }
    }

    auto& node = m_nodes[idx];
    m_next_node_idx = node.m_next_node_idx;
    node.m_event_idx = -1;
    node.m_next_node_idx = -1;
    node.m_idx = -1;
    node.m_owns_variable_pack = false;
    node.m_obj = nullptr;
    node.m_variable_pack = nullptr;
    node.m_node_counter = ++s_GlobalCounter;
    node.m_state = FlowchartContextNode::State::kInvalid;
    ++m_num_allocated_nodes;
    return idx;
}

void FlowchartContext::AllocVariablePack(FlowchartContextNode& node,
                                         const ResEntryPoint& entry_point) {
    FreeVariablePack(node);

    if (entry_point.num_variable_defs != 0) {
        auto* pack = m_allocator.New<VariablePack>();
        pack->Init(m_allocator.GetArg(), &entry_point);
        node.m_variable_pack = pack;
        node.m_owns_variable_pack = true;
    }
}

void FlowchartContext::ProcessContext() {
    if (m_is_processing) {
        _91 = 1;
    } else {
        m_is_processing = true;
        do {
            _91 = 0;
            for (int i = 0, n = m_nodes.size(); i < n; ++i) {
                if (!m_nodes[i].IsInvalidOrFree())
                    _91 = (ProcessContextNode(i) | (_91 != 0)) & 1;
            }
        } while (_91);
        m_is_processing = false;
    }
}

FlowchartObj* FlowchartContext::FindFlowchartObj(ore::StringView name) {
    auto it = std::find_if(m_objs.begin(), m_objs.end(), [&](const FlowchartObj& obj) {
        return name == *obj.GetFlowchart()->name.Get();
    });
    return it == m_objs.end() ? nullptr : it;
}

const FlowchartObj* FlowchartContext::FindFlowchartObj(ore::StringView name) const {
    auto it = std::find_if(m_objs.begin(), m_objs.end(), [&](const FlowchartObj& obj) {
        return name == *obj.GetFlowchart()->name.Get();
    });
    return it == m_objs.end() ? nullptr : it;
}

void FlowchartContext::UnbindAll() {
    Clear();
    for (auto it = m_objs.begin(); it != m_objs.end(); ++it)
        it->GetActBinder().UnbindAll();
}

void FlowchartContext::Clear() {
    for (int i = 0, n = m_nodes.size(); i < n; ++i) {
        FreeVariablePack(m_nodes[i]);
        m_nodes[i].Reset();
        if (i < n - 1) {
            m_nodes[i].m_next_node_idx = i + 1;
            m_nodes[i].m_state = FlowchartContextNode::State::kFree;
        }
    }

    m_next_node_idx = 0;
    m_num_allocated_nodes = 0;
    m_metadata_pack = nullptr;

    while (!m_handlers.Empty()) {
        auto* handler = m_handlers.Front();
        handler->m_list_node.Erase();
        handler->Reset();
    }
}

void FlowchartContext::FreeVariablePack(FlowchartContextNode& node) {
    if (node.m_variable_pack && node.m_owns_variable_pack)
        m_allocator.DeleteAndNull(node.m_variable_pack);

    node.m_variable_pack = nullptr;
    node.m_owns_variable_pack = false;
}

void FlowchartContext::CopyVariablePack(FlowchartContextNode& src, FlowchartContextNode& dst) {
    FreeVariablePack(dst);
    dst.m_variable_pack = src.m_variable_pack;
    dst.m_owns_variable_pack = false;
}

bool FlowchartContext::ProcessContextNode(int node_idx) {
    using State = FlowchartContextNode::State;
    auto& node = GetNode(node_idx);
    while (true) {
        auto* obj = node.m_obj;
        const auto* flowchart = obj->GetFlowchart();
        const auto& event = flowchart->events.Get()[node.m_event_idx];

        int next_event_idx = -1;

        switch (event.type) {
        case ResEvent::EventType::kAction: {
            switch (node.m_state) {
            case State::kNotInvoked: {
                node.m_state = State::kInvoked;

                const auto actor_idx = event.actor_idx;
#ifdef EVFL_VER_LABO
                const auto& actor = flowchart->actors.Get()[actor_idx];
#else
                const auto& actor = obj->GetFlowchart()->actors.Get()[actor_idx];
#endif
                const auto* actions = actor.actions.Get();
                const auto* arg_name = actor.argument_name.Get();
                const auto action_idx = event.actor_action_idx;

                const auto* binding = &obj->GetActBinder().GetBindings()[actor_idx];
                if (!arg_name->empty()) {
                    binding = TrackBackArgumentActor(node_idx, *arg_name);
                    if (!binding)
                        return false;
                }

                const auto* action = binding->GetAction(*actions[action_idx].name.Get());
                const ActionArg arg(this, node_idx, binding->GetUserData(), action->user_data,
                                    node.m_variable_pack, &event);
                ActionDoneHandler done_handler(obj, this, node_idx);
                m_handlers.InsertFront(&done_handler);
                action->handler(arg, std::move(done_handler));
                return false;
            }  // action case State::kNotInvoked
            case State::kDone:
                next_event_idx = event.next_event_idx;
                break;
            default:
                return false;
            }
            break;
        }  // case ResEvent::EventType::kAction

        case ResEvent::EventType::kSwitch: {
            if (node.m_state != State::kNotInvoked)
                return false;

            const auto actor_idx = event.actor_idx;
            const auto& actor = flowchart->actors.Get()[actor_idx];
            const auto* queries = actor.queries.Get();
            const auto* arg_name = actor.argument_name.Get();
            const auto query_idx = event.actor_query_idx;

            const auto* binding = &obj->GetActBinder().GetBindings()[actor_idx];
            if (!arg_name->empty()) {
                binding = TrackBackArgumentActor(node_idx, *arg_name);
                if (!binding)
                    return false;
            }

            const auto* query = binding->GetQuery(*queries[query_idx].name.Get());
            const QueryArg arg(this, node_idx, binding->GetUserData(), query->user_data, &event,
                               node.m_variable_pack);
            const int result = query->handler(arg);

            next_event_idx = 0xffff;
            ore::Array<const ResCase> cases{event.cases.Get(), event.num_cases};
            for (const auto& case_ : cases) {
                if (case_.value == result) {
                    next_event_idx = case_.event_idx;
                    break;
                }
            }
            break;
        }  // case ResEvent::EventType::kSwitch

        case ResEvent::EventType::kFork: {
            if (node.m_state != State::kNotInvoked)
                return false;

            node.m_event_idx = event.join_event_idx;
            node.m_state = State::kInvoked;
            UpdateNodeCounter(node_idx);

            int prev_fork_node_idx = -1;
            int first_fork_node_idx = -1;
            int last_fork_node_idx = -1;

            const ore::Array<const u16> forks{event.fork_event_indices.Get(), event.num_forks};
            for (const auto& fork : forks) {
                last_fork_node_idx = AllocNode();
                auto& fork_node = GetNode(last_fork_node_idx);
                fork_node.m_obj = obj;
                fork_node.m_event_idx = fork;
                fork_node.m_next_node_idx = node_idx;
                fork_node.m_idx = prev_fork_node_idx;
                fork_node.m_state = State::kNotInvoked;
                if (first_fork_node_idx == -1)
                    first_fork_node_idx = last_fork_node_idx;
                CopyVariablePack(node, fork_node);
                prev_fork_node_idx = last_fork_node_idx;
            }

            GetNode(first_fork_node_idx).m_idx = u16(last_fork_node_idx);
            return true;
        }  // case ResEvent::EventType::kFork

        case ResEvent::EventType::kJoin: {
            if (node.m_state != State::kDone)
                return false;
            next_event_idx = event.next_event_idx;
            break;
        }  // case ResEvent::EventType::kJoin

        case ResEvent::EventType::kSubFlow: {
            bool called;
            bool valid_parameters;
            bool tried_invoking = false;
            switch (node.m_state) {
            case State::kNotInvoked: {
                tried_invoking = true;
                node.m_state = State::kInvoked;

                const ore::StringView sub_flow_flowchart = *event.sub_flow_flowchart.Get();
                if (!sub_flow_flowchart.empty()) {
                    obj = FindFlowchartObj(sub_flow_flowchart);
                    if (obj == nullptr) {
                        called = false;
                        valid_parameters = false;
                        break;
                    }
                }

                const int entry_point_idx = obj->GetFlowchart()->entry_point_names.Get()->FindIndex(
                    *event.sub_flow_entry_point.Get());
                if (entry_point_idx == -1) {
                    called = false;
                    valid_parameters = false;
                    break;
                }

                const auto& entry_point = obj->GetFlowchart()->entry_points.Get()[entry_point_idx];

                const u16 main_event_idx = entry_point.main_event_idx;
                if (main_event_idx == 0xffff) {
                    node.m_state = State::kDone;
                    called = false;
                    valid_parameters = true;
                    break;
                }

                // Optimization: if this is a tail call, we don't need to allocate a new node.
                if (event.next_event_idx == 0xffff && event.params.Get() == nullptr) {
                    node.m_obj = obj;
                    node.m_event_idx = main_event_idx;
                    node.m_state = State::kNotInvoked;
                    AllocVariablePack(node, entry_point);
                    UpdateNodeCounter(node_idx);
                } else {
                    const auto sub_flow_node_idx = AllocNode();
                    auto& sub_flow_node = GetNode(sub_flow_node_idx);
                    sub_flow_node.m_obj = obj;
                    sub_flow_node.m_event_idx = main_event_idx;
                    sub_flow_node.m_next_node_idx = node_idx;
                    sub_flow_node.m_idx = sub_flow_node_idx;
                    sub_flow_node.m_state = State::kNotInvoked;
                    AllocVariablePack(sub_flow_node, entry_point);
                }
                CallSubFlowCallback(flowchart, &event, SubFlowCallbackType::kEnter);
                called = true;
                /// @bug valid_parameters should have been initialized to true here.
                /// This bug causes LLVM to generate dumb code like
                ///     mov w8, wzr; mov w9, wzr; orr w8, w8, w9   (for the failure cases above)
                /// or more worryingly:
                ///     mov w8, #1;  orr w8, w8, w9
                /// where w9 is actually undefined!
#ifdef AVOID_UB
                valid_parameters = true;
#endif
                break;
            }  // subflow case State::kNotInvoked
            case State::kInvoked:
                return false;
            case State::kDone:
                next_event_idx = event.next_event_idx;
                CallSubFlowCallback(flowchart, &event, SubFlowCallbackType::kLeave);
                break;
            default:
                break;
            }
            if (tried_invoking)
                return valid_parameters || called;
            break;
        }  // case ResEvent::EventType::kSubFlow
        }

        // We are checking for 0xffff (a 0xffff that comes from the ResEvent data), *not* -1.
        if (next_event_idx == 0xffff) {
            bool ready = false;
            auto* node_2 = &node;
            if (node.m_idx != node_idx) {
                do {
                    node_2 = &GetNode(node_2->m_idx);
                    ready |= node_2->m_state != State::kWaiting;
                } while (node_2->m_idx != node_idx);
            }

            if (!ready) {
                if (node.m_next_node_idx != 0xffff)
                    GetNode(node.m_next_node_idx).m_state = State::kDone;

                int next_node_idx = node_idx;
                int next;
                do {
                    auto& node_to_free = GetNode(next_node_idx);
                    next = node_to_free.m_idx;
                    FreeVariablePack(node_to_free);
                    node_to_free.Reset();
                    node_to_free.m_next_node_idx = m_next_node_idx;
                    node_to_free.m_state = State::kFree;
                    m_next_node_idx = next_node_idx;
                    --m_num_allocated_nodes;
                    next_node_idx = next;
                } while (next != node_idx);
                return true;
            }

            if (event.type == ResEvent::EventType::kAction) {
                node.m_state = State::kWaiting;
                return true;
            }

            node_2->m_idx = node.m_idx;
            auto& node_to_free = GetNode(node_idx);
            FreeVariablePack(node_to_free);
            node_to_free.Reset();
            node_to_free.m_next_node_idx = m_next_node_idx;
            node_to_free.m_state = State::kFree;
            m_next_node_idx = node_idx;
            --m_num_allocated_nodes;
            return true;
        }

        node.m_event_idx = next_event_idx;
        node.m_state = State::kNotInvoked;
        UpdateNodeCounter(node_idx);
    }
}

ActorBinding* FlowchartContext::TrackBackArgumentActor(int node_idx, const ore::StringView& name) {
    if (node_idx == -1)
        return nullptr;

    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    FlowchartObj* obj;
    const ParamAccessor accessor{this, GetNode(node_idx).GetNextNodeIdx()};
    const auto real_name =
        accessor.TrackBackArgument(&metadata, &metadata_pack, &variable_pack, &obj, name);

    if (real_name.empty() || !metadata || !obj)
        return nullptr;

    const auto* param = metadata->Get(real_name, ore::ResMetaData::DataType::kActorIdentifier);
    if (!param)
        return nullptr;

    const ore::StringView actor_name = *param->value.actor.name.Get();
    const ore::StringView actor_sub_name = *param->value.actor.sub_name.Get();

    auto actor = obj->GetFlowchart()->actors.Get();
    for (int i = 0; i < int(obj->GetFlowchart()->num_actors); ++i, ++actor) {
        if (*actor->name.Get() == actor_name && *actor->secondary_name.Get() == actor_sub_name) {
            if (!actor->argument_name.Get()->empty())
                return nullptr;
            return &obj->GetActBinder().GetBindings()[i];
        }
    }

    return nullptr;
}

bool FlowchartContext::IsUsing(const ResFlowchart* flowchart) const {
    auto* obj = FindFlowchartObj(*flowchart->name.Get());
    return obj && obj->GetActBinder().IsUsed();
}

// NON_MATCHING: if (((state | 4) & 7) != 4) -- extremely weird check
bool FlowchartContext::IsPlaying(const ResFlowchart* flowchart) const {
    int state = 2;
    for (int i = 0, n = m_nodes.size(); i < n; ++i) {
        if (m_nodes[i].IsInvalidOrFree()) {
            state = 4;
        } else {
            const auto flowchart_name = ore::StringView(*flowchart->name.Get());
            const auto node_flowchart_name =
                ore::StringView(*m_nodes[i].m_obj->GetFlowchart()->name.Get());
            if (node_flowchart_name == flowchart_name) {
                state = 1;
            } else {
                state = 0;
            }
        }

        if (((state | 4) & 7) != 4)
            break;
    }
    return state != 2;
}

const ore::Array<ActorBinding>*
FlowchartContext::GetUsedResActors(ore::StringView flowchart_name) const {
    auto* obj = FindFlowchartObj(flowchart_name);
    if (!obj)
        return nullptr;
    return obj->GetActBinder().GetUsedResActors();
}

/// Recursively checks subflow calls in the specified entry point for missing flowcharts
/// or entry points.
/// @param result  Optional.
/// @param visited  Visited entry points (one BitArray per flowchart)
/// @param flowchart_idx   Index of the flowchart to which the entry point belongs.
/// @param entry_point_idx  Index of the entry point to be checked.
/// @returns true on success, false on failure
bool CheckSubFlowCalls(FlowchartContext::Builder::BuildResult* result,
                       const ore::IterRange<const ResFlowchart* const*>& flowcharts,
                       ore::Array<ore::BitArray>& visited, int flowchart_idx, int entry_point_idx) {
    if (visited[flowchart_idx].Test(entry_point_idx))
        return true;
    visited[flowchart_idx].Set(entry_point_idx);

    const auto* flowchart = *std::next(flowcharts.begin(), flowchart_idx);
    const auto entry_point_name =
        flowchart->entry_point_names.Get()->GetEntries()[1 + entry_point_idx].GetKey();
    const auto* entry_point = flowchart->GetEntryPoint(entry_point_name);

    for (u16 i = 0; i != entry_point->num_sub_flow_event_indices; ++i) {
        const auto& event = flowchart->events.Get()[entry_point->sub_flow_event_indices.Get()[i]];
        ore::StringView sub_flow_flowchart = *event.sub_flow_flowchart.Get();
        const ore::StringView sub_flow_entry_point = *event.sub_flow_entry_point.Get();

        auto sub_flowchart_idx = flowchart_idx;
        auto* sub_flowchart_res = flowchart;

        if (!sub_flow_flowchart.empty()) {
            const auto it =
                std::find_if(flowcharts.begin(), flowcharts.end(), [=](const ResFlowchart* f) {
                    return sub_flow_flowchart == *f->name.Get();
                });

            if (it == flowcharts.end()) {
                if (result) {
                    result->result =
                        FlowchartContext::Builder::BuildResultType::kResFlowchartNotFound;
                    result->missing_flowchart_name = sub_flow_flowchart;
                    result->missing_entry_point_name = {};
                }
                return false;
            }

            sub_flowchart_idx = std::distance(flowcharts.begin(), it);
            sub_flowchart_res = *it;

        } else {
            sub_flow_flowchart = *flowchart->name.Get();
        }

        const int sub_entry_point_idx =
            sub_flowchart_res->entry_point_names.Get()->FindIndex(sub_flow_entry_point);

        if (sub_entry_point_idx == -1) {
            if (result) {
                result->result = FlowchartContext::Builder::BuildResultType::kEntryPointNotFound;
                result->missing_flowchart_name = sub_flow_flowchart;
                result->missing_entry_point_name = sub_flow_entry_point;
            }
            return false;
        }

        if (!CheckSubFlowCalls(result, flowcharts, visited, sub_flowchart_idx, sub_entry_point_idx))
            return false;
    }

    if (result) {
        result->result = FlowchartContext::Builder::BuildResultType::kSuccess;
        result->missing_flowchart_name = {};
        result->missing_entry_point_name = {};
    }
    return true;
}

bool FlowchartContext::Builder::SetEntryPoint(const ore::StringView& flowchart_name,
                                              const ore::StringView& entry_point_name) {
    return SetEntryPoint(nullptr, flowchart_name, entry_point_name);
}

bool FlowchartContext::Builder::SetEntryPoint(BuildResult* result,
                                              const ore::StringView& flowchart_name,
                                              const ore::StringView& entry_point_name) {
    const auto* flowchart_it =
        std::find_if(m_flowcharts.begin(), m_flowcharts.end(), [=](const ResFlowchart* flowchart) {
            return flowchart_name == *flowchart->name.Get();
        });

    if (flowchart_it == m_flowcharts.end()) {
        if (result) {
            result->result = BuildResultType::kResFlowchartNotFound;
            result->missing_flowchart_name = flowchart_name;
            result->missing_entry_point_name = {};
        }
        return false;
    }

    const auto entry_point_idx =
        (*flowchart_it)->entry_point_names.Get()->FindIndex(entry_point_name);

    if (entry_point_idx == -1) {
        if (result) {
            result->result = BuildResultType::kEntryPointNotFound;
            result->missing_flowchart_name = flowchart_name;
            result->missing_entry_point_name = entry_point_name;
        }
        return false;
    }

    m_flowchart_idx = std::distance(m_flowcharts.begin(), flowchart_it);
    m_entry_point_idx = entry_point_idx;
    if (result) {
        result->result = BuildResultType::kSuccess;
        result->missing_flowchart_name = {};
        result->missing_entry_point_name = {};
    }
    return true;
}

bool FlowchartContext::Builder::BuildImpl(BuildResult* result, FlowchartRange flowcharts,
                                          FlowchartContext* context, AllocateArg allocate_arg,
                                          ore::Buffer flowchart_obj_buffer) {
    context->m_nodes.Reset();
    EvflAllocator allocator{allocate_arg};
    context->m_allocator = allocator;

    const int num_flowcharts = flowcharts.size();

    ore::Array<ore::BitArray> visited_entry_points;
    visited_entry_points.SetBuffer(num_flowcharts, &allocator);
    visited_entry_points.UninitializedDefaultConstructElements();

    const auto clean_up_visited_entry_points = [&] {
        if (auto* data = visited_entry_points.data()) {
            for (auto it = data; it != data + visited_entry_points.size(); ++it)
                it->FreeBufferIfNeeded(&allocator);

            visited_entry_points.DestructElements();
            allocator.Free(data);
        }
    };

    for (int i = 0; i < num_flowcharts; ++i) {
        visited_entry_points[i].AllocateBuffer(&allocator,
                                               (flowcharts.begin()[i])->num_entry_points);
    }

    if (!CheckSubFlowCalls(result, flowcharts, visited_entry_points, m_flowchart_idx,
                           m_entry_point_idx)) {
        clean_up_visited_entry_points();
        return false;
    }

    context->m_objs.ConstructElements(flowchart_obj_buffer);

    for (int i = 0; i < num_flowcharts; ++i) {
        auto* obj = &context->m_objs[i];
        FlowchartObj::Builder obj_builder{flowcharts.begin()[i], &visited_entry_points[i]};

        if (!obj_builder.Build(obj, &context->m_allocator, flowcharts)) {
            clean_up_visited_entry_points();
            context->m_objs.ClearWithoutFreeing();

            if (result) {
                const auto* flowchart = flowcharts.begin()[m_flowchart_idx];
                const ore::StringView name = *flowchart->name.Get();
                const ore::StringView ep_name = flowchart->GetEntryPointName(m_entry_point_idx);
                result->result = BuildResultType::kInvalidOperation;
                result->missing_flowchart_name = name;
                result->missing_entry_point_name = ep_name;
            }
            return false;
        }
    }

    context->m_obj_idx = m_flowchart_idx;
    context->m_active_entry_point_idx = m_entry_point_idx;
    context->m_nodes.Init(&context->m_allocator, 16);
    context->m_nodes.Resize(16);
    context->Clear();
    clean_up_visited_entry_points();

    if (result) {
        result->result = BuildResultType::kSuccess;
        result->missing_flowchart_name = {};
        result->missing_entry_point_name = {};
    }
    return true;
}

bool FlowchartContext::Builder::Build(FlowchartContext* context, AllocateArg allocate_arg) {
    return Build(nullptr, context, allocate_arg);
}

bool FlowchartContext::Builder::Build(BuildResult* result, FlowchartContext* context,
                                      AllocateArg allocate_arg) {
    context->Dispose();

    EvflAllocator allocator{allocate_arg};

    ore::DynArrayList<const ResFlowchart*> flowcharts{&allocator};
    flowcharts.Init(&allocator);
    flowcharts.DeduplicateCopy(m_flowcharts);

    FlowchartRange range{flowcharts};
    ore::Buffer obj_buffer{};
    obj_buffer.Allocate<FlowchartObj>(&allocator, flowcharts.size());

    if (!BuildImpl(result, range, context, allocate_arg, obj_buffer)) {
        obj_buffer.Free(&allocator);
        return false;
    }

    return true;
}

}  // namespace evfl
