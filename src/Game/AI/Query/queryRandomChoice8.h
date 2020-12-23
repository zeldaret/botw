#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class RandomChoice8 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(RandomChoice8, Query)
public:
    explicit RandomChoice8(const InitArg& arg);
    ~RandomChoice8() override;
    int doQuery() override;
};

}  // namespace uking::query
