#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckIsOpenItemCategory : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckIsOpenItemCategory, Query)
public:
    explicit CheckIsOpenItemCategory(const InitArg& arg);
    ~CheckIsOpenItemCategory() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCategory{};
};

}  // namespace uking::query
