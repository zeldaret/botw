#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsArriveAnchorForRain : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsArriveAnchorForRain, Query)
public:
    explicit IsArriveAnchorForRain(const InitArg& arg);
    ~IsArriveAnchorForRain() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
