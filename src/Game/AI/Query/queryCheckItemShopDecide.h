#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckItemShopDecide : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckItemShopDecide, Query)
public:
    explicit CheckItemShopDecide(const InitArg& arg);
    ~CheckItemShopDecide() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
