#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CompareGameDataFloat : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CompareGameDataFloat, Query)
public:
    explicit CompareGameDataFloat(const InitArg& arg);
    ~CompareGameDataFloat() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mGameDataFloatName_A{};
    sead::SafeString mOperator{};
    sead::SafeString mGameDataFloatName_B{};
};

}  // namespace uking::query
