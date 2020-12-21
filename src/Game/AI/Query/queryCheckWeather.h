#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckWeather : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckWeather, Query)
public:
    explicit CheckWeather(const InitArg& arg);
    ~CheckWeather() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
