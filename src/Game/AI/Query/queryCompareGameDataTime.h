#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CompareGameDataTime : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CompareGameDataTime, Query)
public:
    explicit CompareGameDataTime(const InitArg& arg);
    ~CompareGameDataTime() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mGameDataIntMinA{};
    sead::SafeString mGameDataIntSecA{};
    sead::SafeString mGameDataIntMilliA{};
    sead::SafeString mGameDataIntMinB{};
    sead::SafeString mGameDataIntSecB{};
    sead::SafeString mGameDataIntMilliB{};
};

}  // namespace uking::query
