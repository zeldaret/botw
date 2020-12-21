#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsWeaponDrawn : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsWeaponDrawn, Query)
public:
    explicit IsWeaponDrawn(const InitArg& arg);
    ~IsWeaponDrawn() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
