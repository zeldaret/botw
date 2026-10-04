#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckRainRatio : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckRainRatio, Query)
public:
    explicit CheckRainRatio(const InitArg& arg);
    ~CheckRainRatio() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    float* mRainRatio{};
};

}  // namespace uking::query
