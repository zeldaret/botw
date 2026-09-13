#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerWeaponFired : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerWeaponFired, Query)
public:
    explicit CheckPlayerWeaponFired(const InitArg& arg);
    ~CheckPlayerWeaponFired() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCheckFireType{};
};

}  // namespace uking::query
