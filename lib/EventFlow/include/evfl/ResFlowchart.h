#pragma once

#include <ore/BinaryFile.h>
#include <ore/EnumUtil.h>
#include <ore/ResDic.h>
#include <ore/ResMetaData.h>
#include <ore/StringView.h>

namespace ore {
struct ResEndian;
}

namespace evfl {

struct ResActor;

struct ResCase {
    u32 value;
    u16 event_idx;
};

struct ResEvent {
    ORE_ENUM(EventType, kAction, kSwitch, kFork, kJoin, kSubFlow)

    ore::BinTPtr<ore::BinString> name;
    ore::SizedEnum<EventType::Type, u8> type;

    union {
        // Action, Join, Sub flow
        u16 next_event_idx;
        // Switch
        u16 num_cases;
        // Fork
        u16 num_forks;
    };

    union {
        // Action, Switch
        u16 actor_idx;
        // Fork
        u16 join_event_idx;
    };

    union {
        // Action
        u16 actor_action_idx;
        // Switch
        u16 actor_query_idx;
    };

    union {
        // Action, Switch, Sub flow
        ore::BinTPtr<ore::ResMetaData> params;
        // Fork
        ore::BinTPtr<u16> fork_event_indices;
    };

    union {
        // Switch
        ore::BinTPtr<ResCase> cases;
        // Sub flow
        ore::BinTPtr<ore::BinString> sub_flow_flowchart;
    };

    union {
        // Sub flow
        ore::BinTPtr<ore::BinString> sub_flow_entry_point;
    };
};

struct ResVariableDef {
    union Value {
        // Also used for booleans. Anything that is != 0 is treated as true.
        int i;
        float f;
        ore::BinTPtr<int> int_array;
        ore::BinTPtr<float> float_array;
    };

    Value value;
    u16 num;
    ore::SizedEnum<ore::ResMetaData::DataType::Type, u8> type;
};

struct ResEntryPoint {
    ore::BinTPtr<u16> sub_flow_event_indices;
    ore::BinTPtr<ore::ResDic> variable_defs_names;
    ore::BinTPtr<ResVariableDef> variable_defs;
    u16 num_sub_flow_event_indices;
    u16 num_variable_defs;
    u16 main_event_idx;
};

struct ResFlowchart {
    int CountEvent(ResEvent::EventType::Type type) const;

    const ResEntryPoint* GetEntryPoint(const ore::StringView& entry_point_name) const {
        const int idx = entry_point_names.Get()->FindIndex(entry_point_name);
        if (idx == -1)
            return nullptr;

        return entry_points.Get() + idx;
    }

    ore::StringView GetEntryPointName(int idx) const {
        return entry_point_names.Get()->GetEntries()[1 + idx].GetKey();
    }

    /// 'EVFL'
    u32 magic;
    /// String pool offset (relative to this structure)
    u32 string_pool_offset;
    u32 reserved_8;
    u32 reserved_c;
    u16 num_actors;
    u16 num_actions;
    u16 num_queries;
    u16 num_events;
    u16 num_entry_points;
    u16 reserved_1a;
    u16 reserved_1c;
    u16 reserved_1e;
    ore::BinTPtr<ore::BinString> name;
    ore::BinTPtr<ResActor> actors;
    ore::BinTPtr<ResEvent> events;
    ore::BinTPtr<ore::ResDic> entry_point_names;
    ore::BinTPtr<ResEntryPoint> entry_points;
};

void SwapEndian(ore::ResEndian* endian, ResCase* case_);
void SwapEndian(ore::ResEndian* endian, ResEvent* event);
void SwapEndian(ore::ResEndian* endian, ResEntryPoint* entry);
void SwapEndian(ore::ResEndian* endian, ResVariableDef* def);
void SwapEndian(ore::ResEndian* endian, ResFlowchart* flowchart);

}  // namespace evfl
