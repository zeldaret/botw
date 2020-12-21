#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckManufactResult : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckManufactResult, Query)
public:
    explicit CheckManufactResult(const InitArg& arg);
    ~CheckManufactResult() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
