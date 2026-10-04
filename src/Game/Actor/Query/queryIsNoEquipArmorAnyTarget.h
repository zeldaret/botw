#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsNoEquipArmorAnyTarget : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsNoEquipArmorAnyTarget, Query)
public:
    explicit IsNoEquipArmorAnyTarget(const InitArg& arg);
    ~IsNoEquipArmorAnyTarget() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
