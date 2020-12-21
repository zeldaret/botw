#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsCurrentAocFieldStage : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsCurrentAocFieldStage, Query)
public:
    explicit IsCurrentAocFieldStage(const InitArg& arg);
    ~IsCurrentAocFieldStage() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
