#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class ComparePlayerFireResistantLevel : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(ComparePlayerFireResistantLevel, Query)
public:
    explicit ComparePlayerFireResistantLevel(const InitArg& arg);
    ~ComparePlayerFireResistantLevel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
