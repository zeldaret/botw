#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerRideHorse : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerRideHorse, Query)
public:
    explicit CheckPlayerRideHorse(const InitArg& arg);
    ~CheckPlayerRideHorse() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
