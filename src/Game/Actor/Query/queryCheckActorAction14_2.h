#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckActorAction14_2 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckActorAction14_2, Query)
public:
    explicit CheckActorAction14_2(const InitArg& arg);
    ~CheckActorAction14_2() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
