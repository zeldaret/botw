#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckMiniGameTime : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckMiniGameTime, Query)
public:
    explicit CheckMiniGameTime(const InitArg& arg);
    ~CheckMiniGameTime() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mMinute{};
    int* mSecond{};
    int* mConditionType{};
};

}  // namespace uking::query
