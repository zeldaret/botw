#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CompareGameDataInt : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CompareGameDataInt, Query)
public:
    explicit CompareGameDataInt(const InitArg& arg);
    ~CompareGameDataInt() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mGameDataIntName_A{};
    sead::SafeString mOperator{};
    sead::SafeString mGameDataIntName_B{};
};

}  // namespace uking::query
