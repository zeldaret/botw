#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsRest : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsRest, Query)
public:
    explicit IsRest(const InitArg& arg);
    ~IsRest() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
