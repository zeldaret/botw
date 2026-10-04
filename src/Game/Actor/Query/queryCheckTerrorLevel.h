#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckTerrorLevel : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckTerrorLevel, Query)
public:
    explicit CheckTerrorLevel(const InitArg& arg);
    ~CheckTerrorLevel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
