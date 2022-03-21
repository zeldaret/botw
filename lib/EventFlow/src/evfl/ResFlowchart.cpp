#include <algorithm>
#include <evfl/ResActor.h>
#include <evfl/ResFlowchart.h>
#include <ore/Array.h>
#include <ore/ResDic.h>
#include <ore/ResEndian.h>

namespace evfl {

using ore::SwapEndian;

static void SwapEndianForFlowchartData(ore::ResEndian* endian, ResFlowchart* flowchart) {
    ore::Array<ResActor> actors{flowchart->actors.ToPtr(endian->base), flowchart->num_actors};
    for (auto& actor : actors)
        SwapEndian(endian, &actor);

    ore::Array<ResEvent> events{flowchart->events.ToPtr(endian->base), flowchart->num_events};
    for (auto& event : events)
        SwapEndian(endian, &event);

    if (auto* names = flowchart->entry_point_names.ToPtr(endian->base))
        SwapEndian(endian, names);

    ore::Array<ResEntryPoint> entry_points{flowchart->entry_points.ToPtr(endian->base),
                                           flowchart->num_entry_points};
    for (auto& entry : entry_points)
        SwapEndian(endian, &entry);
}

static void SwapEndianForFlowchartFields(ore::ResEndian* endian, ResFlowchart* flowchart) {
    SwapEndian(&flowchart->num_actors);
    SwapEndian(&flowchart->num_actions);
    SwapEndian(&flowchart->num_queries);
    SwapEndian(&flowchart->num_events);
    SwapEndian(&flowchart->num_entry_points);
}

void SwapEndian(ore::ResEndian* endian, ResFlowchart* flowchart) {
    if (endian->is_serializing) {
        SwapEndianForFlowchartData(endian, flowchart);
        SwapEndianForFlowchartFields(endian, flowchart);
    } else {
        SwapEndianForFlowchartFields(endian, flowchart);
        SwapEndianForFlowchartData(endian, flowchart);
    }
}

int ResFlowchart::CountEvent(ResEvent::EventType::Type type) const {
    ore::Array<const ResEvent> array{events.Get(), num_events};
    return std::count_if(array.begin(), array.end(),
                         [type](const ResEvent& event) { return event.type == type; });
}

void SwapEndian(ore::ResEndian* endian, ResCase* case_) {
    SwapEndian(&case_->event_idx);
    SwapEndian(&case_->value);
}

static void SwapEndianForEventData(ore::ResEndian* endian, ResEvent* event) {
    switch (event->type) {
    case ResEvent::EventType::kAction:
        if (auto* params = event->params.ToPtr(endian->base))
            SwapEndian(endian, params);
        break;
    case ResEvent::EventType::kSwitch: {
        ore::Array<ResCase> cases{event->cases.ToPtr(endian->base), event->num_cases};
        for (auto& case_ : cases)
            SwapEndian(endian, &case_);
        if (auto* params = event->params.ToPtr(endian->base))
            SwapEndian(endian, params);
        break;
    }
    case ResEvent::EventType::kFork: {
        ore::Array<u16> forks{event->fork_event_indices.ToPtr(endian->base), event->num_forks};
        for (auto& fork : forks)
            SwapEndian(&fork);
        break;
    }
    case ResEvent::EventType::kJoin:
        break;
    case ResEvent::EventType::kSubFlow:
        if (auto* params = event->params.ToPtr(endian->base))
            SwapEndian(endian, params);
        break;
    }
}

static void SwapEndianForEventFields(ore::ResEndian* endian, ResEvent* event) {
    switch (event->type) {
    case ResEvent::EventType::kAction:
        SwapEndian(&event->next_event_idx);
        SwapEndian(&event->actor_idx);
        SwapEndian(&event->actor_action_idx);
        break;
    case ResEvent::EventType::kSwitch:
        SwapEndian(&event->next_event_idx);
        SwapEndian(&event->actor_idx);
        SwapEndian(&event->actor_query_idx);
        break;
    case ResEvent::EventType::kFork:
        SwapEndian(&event->num_forks);
        SwapEndian(&event->join_event_idx);
        break;
    case ResEvent::EventType::kJoin:
    case ResEvent::EventType::kSubFlow:
        SwapEndian(&event->next_event_idx);
        break;
    }
}

void SwapEndian(ore::ResEndian* endian, ResEvent* event) {
    if (endian->is_serializing) {
        SwapEndianForEventData(endian, event);
        SwapEndianForEventFields(endian, event);
    } else {
        SwapEndianForEventFields(endian, event);
        SwapEndianForEventData(endian, event);
    }
}

static void SwapEndianImpl(ore::ResEndian* endian, ResEntryPoint* entry) {
    ore::Array<u16> sub_flow_event_indices{entry->sub_flow_event_indices.ToPtr(endian->base),
                                           entry->num_sub_flow_event_indices};
    for (auto& x : sub_flow_event_indices)
        SwapEndian(&x);

    auto* variable_def_names = entry->variable_defs_names.ToPtr(endian->base);
    if (variable_def_names)
        SwapEndian(endian, variable_def_names);

    ore::Array<ResVariableDef> variable_defs{entry->variable_defs.ToPtr(endian->base),
                                             entry->num_variable_defs};
    for (auto& def : variable_defs)
        SwapEndian(endian, &def);
}

void SwapEndian(ore::ResEndian* endian, ResEntryPoint* entry) {
    if (endian->is_serializing) {
        SwapEndianImpl(endian, entry);
        SwapEndian(&entry->main_event_idx);
        SwapEndian(&entry->num_sub_flow_event_indices);
        SwapEndian(&entry->num_variable_defs);
    } else {
        SwapEndian(&entry->main_event_idx);
        SwapEndian(&entry->num_sub_flow_event_indices);
        SwapEndian(&entry->num_variable_defs);
        SwapEndianImpl(endian, entry);
    }
}

static void SwapEndianImpl(ore::ResEndian* endian, ResVariableDef* def) {
    switch (def->type) {
    case ore::ResMetaData::DataType::kIntArray: {
        const auto num = def->num;
        ore::Array<int> array{def->value.int_array.ToPtr(endian->base), num};
        for (auto& x : array)
            SwapEndian(&x);
        break;
    }
    case ore::ResMetaData::DataType::kFloatArray: {
        const auto num = def->num;
        ore::Array<float> array{def->value.float_array.ToPtr(endian->base), num};
        for (auto& x : array)
            SwapEndian(reinterpret_cast<u32*>(&x));
        break;
    }
    default:
        break;
    }
}

static bool IsScalarVariableDef(ResVariableDef* def) {
    using Type = ore::ResMetaData::DataType::Type;
    return def->type == Type::kInt || def->type == Type::kBool || def->type == Type::kFloat;
}

void SwapEndian(ore::ResEndian* endian, ResVariableDef* def) {
    if (endian->is_serializing) {
        SwapEndianImpl(endian, def);
        SwapEndian(&def->num);
        if (IsScalarVariableDef(def))
            SwapEndian(&def->value.i);
    } else {
        SwapEndian(&def->num);
        if (IsScalarVariableDef(def))
            SwapEndian(&def->value.i);
        SwapEndianImpl(endian, def);
    }
}

}  // namespace evfl
