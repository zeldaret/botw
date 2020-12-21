#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasPorchItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasPorchItem, Query)
public:
    explicit HasPorchItem(const InitArg& arg);
    ~HasPorchItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
    sead::SafeString mPorchItemName{};
};

}  // namespace uking::query
