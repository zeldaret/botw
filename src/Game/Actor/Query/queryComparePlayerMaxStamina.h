#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class ComparePlayerMaxStamina : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(ComparePlayerMaxStamina, Query)
public:
    explicit ComparePlayerMaxStamina(const InitArg& arg);
    ~ComparePlayerMaxStamina() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
