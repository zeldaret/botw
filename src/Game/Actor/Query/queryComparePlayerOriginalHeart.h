#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class ComparePlayerOriginalHeart : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(ComparePlayerOriginalHeart, Query)
public:
    explicit ComparePlayerOriginalHeart(const InitArg& arg);
    ~ComparePlayerOriginalHeart() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
