#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsCurrentCDungeonStage : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsCurrentCDungeonStage, Query)
public:
    explicit IsCurrentCDungeonStage(const InitArg& arg);
    ~IsCurrentCDungeonStage() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
