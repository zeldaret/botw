#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class EnemyDieCheck : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(EnemyDieCheck, Query)
public:
    explicit EnemyDieCheck(const InitArg& arg);
    ~EnemyDieCheck() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
