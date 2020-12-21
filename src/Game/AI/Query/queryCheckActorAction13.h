#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckActorAction13 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckActorAction13, Query)
public:
    explicit CheckActorAction13(const InitArg& arg);
    ~CheckActorAction13() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
