#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasSetItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasSetItem, Query)
public:
    explicit HasSetItem(const InitArg& arg);
    ~HasSetItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
    sead::SafeString mItemName{};
};

}  // namespace uking::query
