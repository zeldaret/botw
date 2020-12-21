#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsIgnitionByArrowFire : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsIgnitionByArrowFire, Query)
public:
    explicit IsIgnitionByArrowFire(const InitArg& arg);
    ~IsIgnitionByArrowFire() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
