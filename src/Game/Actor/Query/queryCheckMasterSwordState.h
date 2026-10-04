#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckMasterSwordState : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckMasterSwordState, Query)
public:
    explicit CheckMasterSwordState(const InitArg& arg);
    ~CheckMasterSwordState() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
