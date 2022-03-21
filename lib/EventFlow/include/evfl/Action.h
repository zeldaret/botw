#pragma once

#include <evfl/Param.h>
#include <ore/EnumUtil.h>
#include <ore/IntrusiveList.h>
#include <utility>

namespace evfl {

class FlowchartContext;
class FlowchartContextNode;
class FlowchartObj;
struct ResClip;
struct ResEvent;
struct ResOneshot;
class TimelineObj;
class VariablePack;

ORE_VALUED_ENUM(TriggerType, kFlowchart = 0, kClipEnter = 1, kClipLeave = 2, kOneshot = 3,
                kNormal = 0, kEnter = 1, kLeave = 2)

class ActionDoneHandler {
public:
    ActionDoneHandler() = default;
    ActionDoneHandler(FlowchartObj* obj, FlowchartContext* context, int node_idx);
    explicit ActionDoneHandler(TimelineObj* obj) : m_is_flowchart(false) { m_timeline_obj = obj; }
    ~ActionDoneHandler() { m_list_node.Erase(); }

    ActionDoneHandler(const ActionDoneHandler&) = delete;
    auto operator=(const ActionDoneHandler&) = delete;

    ActionDoneHandler(ActionDoneHandler&& other) noexcept { *this = std::move(other); }

    ActionDoneHandler& operator=(ActionDoneHandler&& other) noexcept {
        m_context = other.m_context;
        m_node_idx = other.m_node_idx;
        m_obj = other.m_obj;
        m_node_counter = other.m_node_counter;
        m_handled = other.m_handled;
        m_is_flowchart = other.m_is_flowchart;
        m_list_node = std::move(other.m_list_node);

        other.m_context = nullptr;
        other.m_node_idx = -1;
        other.m_node_counter = -1;
        other.m_obj = nullptr;
        other.m_handled = false;
        other.m_is_flowchart = true;

        return *this;
    }

    FlowchartContextNode* GetContextNode();
    void InvokeFromFlowchartImpl();
    void InvokeFromTimelineImpl();
    bool IsWaitingJoin();
    bool CancelWaiting();

    void Reset() {
        m_context = nullptr;
        m_obj = nullptr;
        m_node_idx = -1;
        m_node_counter = -1;
        m_handled = false;
        m_is_flowchart = true;
    }

    static constexpr size_t GetListNodeOffset() { return offsetof(ActionDoneHandler, m_list_node); }

private:
    friend class FlowchartContext;

    ore::IntrusiveListNode m_list_node;
    FlowchartContext* m_context = nullptr;
    int m_node_idx = -1;
    int m_node_counter = -1;
    union {
        FlowchartObj* m_obj = nullptr;
        TimelineObj* m_timeline_obj;
    };
    bool m_handled = false;
    bool m_is_flowchart = true;
};

struct ActionArg {
    ActionArg(FlowchartContext* context, int node_idx, void* actor_user_data_,
              void* action_user_data_, VariablePack* variable_pack_, const ResEvent* event_)
        : param_accessor(context, node_idx), actor_user_data(actor_user_data_),
          action_user_data(action_user_data_), flowchart_ctx(context),
          variable_pack(variable_pack_), res(event_), timeline_time_delta(0.0),
          trigger_type(TriggerType::kFlowchart) {}

    ActionArg(const ResClip* clip, void* actor_user_data_, void* action_user_data_,
              float timeline_time_delta_, TriggerType::Type type, const ore::ResMetaData* params)
        : param_accessor(params), actor_user_data(actor_user_data_),
          action_user_data(action_user_data_), res(clip), timeline_time_delta(timeline_time_delta_),
          trigger_type(type) {}

    ActionArg(const ResOneshot* oneshot, void* actor_user_data_, void* action_user_data_,
              float timeline_time_delta_, const ore::ResMetaData* params)
        : param_accessor(params), actor_user_data(actor_user_data_),
          action_user_data(action_user_data_), res(oneshot),
          timeline_time_delta(timeline_time_delta_), trigger_type(TriggerType::kOneshot) {
        res.oneshot = oneshot;
    }

    ParamAccessor param_accessor;
    void* actor_user_data = nullptr;
    void* action_user_data = nullptr;
    FlowchartContext* flowchart_ctx = nullptr;
    VariablePack* variable_pack = nullptr;
    union Res {
        explicit Res(const ResEvent* e) : event(e) {}
        explicit Res(const ResClip* c) : clip(c) {}
        explicit Res(const ResOneshot* o) : oneshot(o) {}

        const ResEvent* event;
        const ResClip* clip;
        const ResOneshot* oneshot;
    } res;
    float timeline_time_delta{};
    TriggerType::Type trigger_type{};
};

}  // namespace evfl
