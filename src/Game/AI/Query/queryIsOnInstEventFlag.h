#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsOnInstEventFlag : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsOnInstEventFlag, Query)
public:
    explicit IsOnInstEventFlag(const InitArg& arg);
    ~IsOnInstEventFlag() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
