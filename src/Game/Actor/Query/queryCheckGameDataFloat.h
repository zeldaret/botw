#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckGameDataFloat : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckGameDataFloat, Query)
public:
    explicit CheckGameDataFloat(const InitArg& arg);
    ~CheckGameDataFloat() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    float* mValue{};
    sead::SafeString mGameDataFloatName{};
    sead::SafeString mOperator{};
};

}  // namespace uking::query
