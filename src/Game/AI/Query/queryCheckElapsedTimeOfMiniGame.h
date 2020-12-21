#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckElapsedTimeOfMiniGame : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckElapsedTimeOfMiniGame, Query)
public:
    explicit CheckElapsedTimeOfMiniGame(const InitArg& arg);
    ~CheckElapsedTimeOfMiniGame() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
