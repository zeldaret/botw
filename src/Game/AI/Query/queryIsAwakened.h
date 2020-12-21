#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsAwakened : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsAwakened, Query)
public:
    explicit IsAwakened(const InitArg& arg);
    ~IsAwakened() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
