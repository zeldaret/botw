#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckShopSelectedItemName : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckShopSelectedItemName, Query)
public:
    explicit CheckShopSelectedItemName(const InitArg& arg);
    ~CheckShopSelectedItemName() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mPorchItemName{};
};

}  // namespace uking::query
