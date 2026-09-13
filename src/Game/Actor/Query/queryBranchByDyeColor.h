#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class BranchByDyeColor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(BranchByDyeColor, Query)
public:
    explicit BranchByDyeColor(const InitArg& arg);
    ~BranchByDyeColor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
