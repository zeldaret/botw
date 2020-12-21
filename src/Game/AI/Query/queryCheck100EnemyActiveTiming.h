#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class Check100EnemyActiveTiming : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(Check100EnemyActiveTiming, Query)
public:
    explicit Check100EnemyActiveTiming(const InitArg& arg);
    ~Check100EnemyActiveTiming() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
