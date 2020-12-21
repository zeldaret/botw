#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsTerrorDisappeared : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsTerrorDisappeared, Query)
public:
    explicit IsTerrorDisappeared(const InitArg& arg);
    ~IsTerrorDisappeared() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
