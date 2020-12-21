#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsPlayerGrounded : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsPlayerGrounded, Query)
public:
    explicit IsPlayerGrounded(const InitArg& arg);
    ~IsPlayerGrounded() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
