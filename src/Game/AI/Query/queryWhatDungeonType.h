#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class WhatDungeonType : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(WhatDungeonType, Query)
public:
    explicit WhatDungeonType(const InitArg& arg);
    ~WhatDungeonType() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
