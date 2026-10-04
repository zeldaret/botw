#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckTime : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckTime, Query)
public:
    explicit CheckTime(const InitArg& arg);
    ~CheckTime() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mHour{};
    int* mMinute{};
    sead::SafeString mConditionType{};
};

}  // namespace uking::query
