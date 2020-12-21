#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDistanceFromPlayer : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDistanceFromPlayer, Query)
public:
    explicit CheckDistanceFromPlayer(const InitArg& arg);
    ~CheckDistanceFromPlayer() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    float* mBorder{};
};

}  // namespace uking::query
