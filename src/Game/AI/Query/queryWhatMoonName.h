#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class WhatMoonName : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(WhatMoonName, Query)
public:
    explicit WhatMoonName(const InitArg& arg);
    ~WhatMoonName() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
