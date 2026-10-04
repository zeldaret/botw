#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckReceiveTerrorLevel : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckReceiveTerrorLevel, Query)
public:
    explicit CheckReceiveTerrorLevel(const InitArg& arg);
    ~CheckReceiveTerrorLevel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
