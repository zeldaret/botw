#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class RandomChoiceExceptOnFlag : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(RandomChoiceExceptOnFlag, Query)
public:
    explicit RandomChoiceExceptOnFlag(const InitArg& arg);
    ~RandomChoiceExceptOnFlag() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mCheckFlag0{};
    sead::SafeString mCheckFlag1{};
    sead::SafeString mCheckFlag2{};
    sead::SafeString mCheckFlag3{};
    sead::SafeString mCheckFlag4{};
    sead::SafeString mCheckFlag5{};
    sead::SafeString mCheckFlag6{};
    sead::SafeString mCheckFlag7{};
    sead::SafeString mCheckFlag8{};
    sead::SafeString mCheckFlag9{};
};

}  // namespace uking::query
