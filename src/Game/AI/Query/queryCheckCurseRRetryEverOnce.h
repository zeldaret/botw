#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckCurseRRetryEverOnce : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckCurseRRetryEverOnce, Query)
public:
    explicit CheckCurseRRetryEverOnce(const InitArg& arg);
    ~CheckCurseRRetryEverOnce() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCurseRType{};
};

}  // namespace uking::query
