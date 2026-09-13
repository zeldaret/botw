#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsCurrentMainFieldDungeonStage : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsCurrentMainFieldDungeonStage, Query)
public:
    explicit IsCurrentMainFieldDungeonStage(const InitArg& arg);
    ~IsCurrentMainFieldDungeonStage() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
