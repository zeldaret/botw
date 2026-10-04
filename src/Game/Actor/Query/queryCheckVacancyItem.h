#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckVacancyItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckVacancyItem, Query)
public:
    explicit CheckVacancyItem(const InitArg& arg);
    ~CheckVacancyItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
};

}  // namespace uking::query
