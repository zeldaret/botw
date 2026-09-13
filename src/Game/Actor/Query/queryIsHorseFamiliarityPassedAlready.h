#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsHorseFamiliarityPassedAlready : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsHorseFamiliarityPassedAlready, Query)
public:
    explicit IsHorseFamiliarityPassedAlready(const InitArg& arg);
    ~IsHorseFamiliarityPassedAlready() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
