#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerFastFadeDead : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerFastFadeDead, Query)
public:
    explicit CheckPlayerFastFadeDead(const InitArg& arg);
    ~CheckPlayerFastFadeDead() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
