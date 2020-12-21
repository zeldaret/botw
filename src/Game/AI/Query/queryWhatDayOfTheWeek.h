#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class WhatDayOfTheWeek : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(WhatDayOfTheWeek, Query)
public:
    explicit WhatDayOfTheWeek(const InitArg& arg);
    ~WhatDayOfTheWeek() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
