#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerRideSunazarashi : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerRideSunazarashi, Query)
public:
    explicit CheckPlayerRideSunazarashi(const InitArg& arg);
    ~CheckPlayerRideSunazarashi() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mSunazarashiType{};
    sead::SafeString mSunazarashiName{};
};

}  // namespace uking::query
