#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPorchInItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPorchInItem, Query)
public:
    explicit CheckPorchInItem(const InitArg& arg);
    ~CheckPorchInItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mPorchItemName{};
};

}  // namespace uking::query
