#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckCurrentMap : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckCurrentMap, Query)
public:
    explicit CheckCurrentMap(const InitArg& arg);
    ~CheckCurrentMap() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mMapName{};
};

}  // namespace uking::query
