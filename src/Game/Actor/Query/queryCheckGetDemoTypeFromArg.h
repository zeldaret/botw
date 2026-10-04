#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckGetDemoTypeFromArg : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckGetDemoTypeFromArg, Query)
public:
    explicit CheckGetDemoTypeFromArg(const InitArg& arg);
    ~CheckGetDemoTypeFromArg() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    bool* mUseLastTryGetItemName{};
    sead::SafeString mCheckTargetActorName{};
};

}  // namespace uking::query
