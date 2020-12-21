#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class RandomChoice2 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(RandomChoice2, Query)
public:
    explicit RandomChoice2(const InitArg& arg);
    ~RandomChoice2() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
