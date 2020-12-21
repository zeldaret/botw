#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerTemperatureCondition : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerTemperatureCondition, Query)
public:
    explicit CheckPlayerTemperatureCondition(const InitArg& arg);
    ~CheckPlayerTemperatureCondition() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
