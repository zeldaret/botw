#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckItemShopSelect : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckItemShopSelect, Query)
public:
    explicit CheckItemShopSelect(const InitArg& arg);
    ~CheckItemShopSelect() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
