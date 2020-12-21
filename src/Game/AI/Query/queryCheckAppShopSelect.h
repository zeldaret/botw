#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckAppShopSelect : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckAppShopSelect, Query)
public:
    explicit CheckAppShopSelect(const InitArg& arg);
    ~CheckAppShopSelect() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
