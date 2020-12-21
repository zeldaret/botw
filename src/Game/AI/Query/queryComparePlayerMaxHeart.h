#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class ComparePlayerMaxHeart : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(ComparePlayerMaxHeart, Query)
public:
    explicit ComparePlayerMaxHeart(const InitArg& arg);
    ~ComparePlayerMaxHeart() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
