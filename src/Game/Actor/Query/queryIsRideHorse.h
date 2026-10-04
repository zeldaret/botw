#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsRideHorse : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsRideHorse, Query)
public:
    explicit IsRideHorse(const InitArg& arg);
    ~IsRideHorse() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
