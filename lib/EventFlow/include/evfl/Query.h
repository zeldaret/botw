#pragma once

#include <evfl/Param.h>
#include <ore/EnumUtil.h>

namespace evfl {

class FlowchartContext;
struct ResEvent;
class VariablePack;

ORE_ENUM(QueryValueType, kBool, kInt, kFloat, kString, kConst)

struct QueryArg {
    QueryArg(FlowchartContext* context, int node_idx, void* actor_user_data_,
             void* query_user_data_, const ResEvent* event_, VariablePack* variable_pack_)
        : actor_user_data(actor_user_data_), query_user_data(query_user_data_), main_event(event_),
          flowchart_ctx(context), variable_pack(variable_pack_), param_accessor(context, node_idx) {
    }

    void* actor_user_data;
    void* query_user_data;
    const ResEvent* main_event;
    FlowchartContext* flowchart_ctx;
    VariablePack* variable_pack;
    ParamAccessor param_accessor;
};

}  // namespace evfl
