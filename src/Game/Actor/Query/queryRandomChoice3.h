#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class RandomChoice3 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(RandomChoice3, Query)
public:
    explicit RandomChoice3(const InitArg& arg);
    ~RandomChoice3() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
