#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckProConUse : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckProConUse, Query)
public:
    explicit CheckProConUse(const InitArg& arg);
    ~CheckProConUse() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
