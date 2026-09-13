#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckActorAction : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckActorAction, Query)
public:
    explicit CheckActorAction(const InitArg& arg);
    ~CheckActorAction() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mActionName{};
};

}  // namespace uking::query
