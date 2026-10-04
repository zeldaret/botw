#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckContainerItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckContainerItem, Query)
public:
    explicit CheckContainerItem(const InitArg& arg);
    ~CheckContainerItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mPorchItemName{};
};

}  // namespace uking::query
