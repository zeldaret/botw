#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckItemShopSelectBuy : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckItemShopSelectBuy, Query)
public:
    explicit CheckItemShopSelectBuy(const InitArg& arg);
    ~CheckItemShopSelectBuy() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
