#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckAppPoint : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckAppPoint, Query)
public:
    explicit CheckAppPoint(const InitArg& arg);
    ~CheckAppPoint() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
