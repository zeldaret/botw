#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsEquippedWithLowerBody : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsEquippedWithLowerBody, Query)
public:
    explicit IsEquippedWithLowerBody(const InitArg& arg);
    ~IsEquippedWithLowerBody() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
