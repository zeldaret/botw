#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CountFlag4 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CountFlag4, Query)
public:
    explicit CountFlag4(const InitArg& arg);
    ~CountFlag4() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mGameDataFlagNo0{};
    sead::SafeString mGameDataFlagNo1{};
    sead::SafeString mGameDataFlagNo2{};
    sead::SafeString mGameDataFlagNo3{};
    sead::SafeString mGameDataFlagNo4{};
};

}  // namespace uking::query
