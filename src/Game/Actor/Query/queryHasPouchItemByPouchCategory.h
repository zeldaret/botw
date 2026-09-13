#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasPouchItemByPouchCategory : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasPouchItemByPouchCategory, Query)
public:
    explicit HasPouchItemByPouchCategory(const InitArg& arg);
    ~HasPouchItemByPouchCategory() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCategory{};
    int* mCount{};
};

}  // namespace uking::query
