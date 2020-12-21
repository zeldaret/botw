#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class WhatCurrentItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(WhatCurrentItem, Query)
public:
    explicit WhatCurrentItem(const InitArg& arg);
    ~WhatCurrentItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
