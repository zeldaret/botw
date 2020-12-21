#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsWaitRevival : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsWaitRevival, Query)
public:
    explicit IsWaitRevival(const InitArg& arg);
    ~IsWaitRevival() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
