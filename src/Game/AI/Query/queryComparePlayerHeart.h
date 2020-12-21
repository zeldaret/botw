#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class ComparePlayerHeart : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(ComparePlayerHeart, Query)
public:
    explicit ComparePlayerHeart(const InitArg& arg);
    ~ComparePlayerHeart() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
