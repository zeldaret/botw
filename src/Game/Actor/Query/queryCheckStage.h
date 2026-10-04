#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckStage : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckStage, Query)
public:
    explicit CheckStage(const InitArg& arg);
    ~CheckStage() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
