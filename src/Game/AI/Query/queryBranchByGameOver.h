#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class BranchByGameOver : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(BranchByGameOver, Query)
public:
    explicit BranchByGameOver(const InitArg& arg);
    ~BranchByGameOver() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
