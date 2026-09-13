#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsCurrentMainFieldStage : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsCurrentMainFieldStage, Query)
public:
    explicit IsCurrentMainFieldStage(const InitArg& arg);
    ~IsCurrentMainFieldStage() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
