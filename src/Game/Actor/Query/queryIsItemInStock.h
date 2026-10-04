#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsItemInStock : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsItemInStock, Query)
public:
    explicit IsItemInStock(const InitArg& arg);
    ~IsItemInStock() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
