#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDyeShopSelect : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDyeShopSelect, Query)
public:
    explicit CheckDyeShopSelect(const InitArg& arg);
    ~CheckDyeShopSelect() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
