#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDistanceForWarp : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDistanceForWarp, Query)
public:
    explicit CheckDistanceForWarp(const InitArg& arg);
    ~CheckDistanceForWarp() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mWarpDestMapName{};
    sead::SafeString mWarpDestPosName{};
};

}  // namespace uking::query
