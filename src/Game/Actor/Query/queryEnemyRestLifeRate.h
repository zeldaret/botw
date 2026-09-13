#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class EnemyRestLifeRate : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(EnemyRestLifeRate, Query)
public:
    explicit EnemyRestLifeRate(const InitArg& arg);
    ~EnemyRestLifeRate() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    float* mCheckRate{};
};

}  // namespace uking::query
