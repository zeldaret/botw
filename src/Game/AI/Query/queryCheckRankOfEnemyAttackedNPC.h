#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckRankOfEnemyAttackedNPC : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckRankOfEnemyAttackedNPC, Query)
public:
    explicit CheckRankOfEnemyAttackedNPC(const InitArg& arg);
    ~CheckRankOfEnemyAttackedNPC() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
