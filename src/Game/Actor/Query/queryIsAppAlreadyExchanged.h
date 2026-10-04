#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsAppAlreadyExchanged : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsAppAlreadyExchanged, Query)
public:
    explicit IsAppAlreadyExchanged(const InitArg& arg);
    ~IsAppAlreadyExchanged() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
