#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class RandomChoice4 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(RandomChoice4, Query)
public:
    explicit RandomChoice4(const InitArg& arg);
    ~RandomChoice4() override;
    int doQuery() override;
};

}  // namespace uking::query
