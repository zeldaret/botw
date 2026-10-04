#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckWarpMist : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckWarpMist, Query)
public:
    explicit CheckWarpMist(const InitArg& arg);
    ~CheckWarpMist() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
