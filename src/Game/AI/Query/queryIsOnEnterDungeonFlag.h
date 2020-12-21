#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsOnEnterDungeonFlag : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsOnEnterDungeonFlag, Query)
public:
    explicit IsOnEnterDungeonFlag(const InitArg& arg);
    ~IsOnEnterDungeonFlag() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
