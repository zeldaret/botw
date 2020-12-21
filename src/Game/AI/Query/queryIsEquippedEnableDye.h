#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsEquippedEnableDye : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsEquippedEnableDye, Query)
public:
    explicit IsEquippedEnableDye(const InitArg& arg);
    ~IsEquippedEnableDye() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
