#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsSuccessEndLastDemoAction : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsSuccessEndLastDemoAction, Query)
public:
    explicit IsSuccessEndLastDemoAction(const InitArg& arg);
    ~IsSuccessEndLastDemoAction() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
