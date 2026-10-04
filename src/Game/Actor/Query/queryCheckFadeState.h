#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckFadeState : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckFadeState, Query)
public:
    explicit CheckFadeState(const InitArg& arg);
    ~CheckFadeState() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mFadeType{};
    int* mState{};
};

}  // namespace uking::query
