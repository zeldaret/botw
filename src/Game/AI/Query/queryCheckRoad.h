#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckRoad : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckRoad, Query)
public:
    explicit CheckRoad(const InitArg& arg);
    ~CheckRoad() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mRoadId{};
};

}  // namespace uking::query
