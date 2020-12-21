#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckAddPorchItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckAddPorchItem, Query)
public:
    explicit CheckAddPorchItem(const InitArg& arg);
    ~CheckAddPorchItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
    sead::SafeString mPorchItemName{};
};

}  // namespace uking::query
