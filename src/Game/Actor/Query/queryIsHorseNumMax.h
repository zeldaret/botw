#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsHorseNumMax : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsHorseNumMax, Query)
public:
    explicit IsHorseNumMax(const InitArg& arg);
    ~IsHorseNumMax() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
