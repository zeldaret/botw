#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckSellResult : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckSellResult, Query)
public:
    explicit CheckSellResult(const InitArg& arg);
    ~CheckSellResult() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
