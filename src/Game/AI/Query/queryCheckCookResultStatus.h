#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckCookResultStatus : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckCookResultStatus, Query)
public:
    explicit CheckCookResultStatus(const InitArg& arg);
    ~CheckCookResultStatus() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCheckType{};
    void* mCurrentCookResultHolder{};
};

}  // namespace uking::query
