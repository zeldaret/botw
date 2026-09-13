#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerState : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerState, Query)
public:
    explicit CheckPlayerState(const InitArg& arg);
    ~CheckPlayerState() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mPlayerState{};
};

}  // namespace uking::query
