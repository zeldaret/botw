#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckBalladOfHeroActiveTiming : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckBalladOfHeroActiveTiming, Query)
public:
    explicit CheckBalladOfHeroActiveTiming(const InitArg& arg);
    ~CheckBalladOfHeroActiveTiming() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
