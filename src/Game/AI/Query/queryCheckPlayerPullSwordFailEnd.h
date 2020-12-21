#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerPullSwordFailEnd : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerPullSwordFailEnd, Query)
public:
    explicit CheckPlayerPullSwordFailEnd(const InitArg& arg);
    ~CheckPlayerPullSwordFailEnd() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
