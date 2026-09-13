#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckEatActor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckEatActor, Query)
public:
    explicit CheckEatActor(const InitArg& arg);
    ~CheckEatActor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mActorName{};
    sead::SafeString* mPrevEatActorName{};
};

}  // namespace uking::query
