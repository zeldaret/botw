#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsEquipedDyedArmor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsEquipedDyedArmor, Query)
public:
    explicit IsEquipedDyedArmor(const InitArg& arg);
    ~IsEquipedDyedArmor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
