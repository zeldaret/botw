#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckWeaponVacancyItem : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckWeaponVacancyItem, Query)
public:
    explicit CheckWeaponVacancyItem(const InitArg& arg);
    ~CheckWeaponVacancyItem() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
};

}  // namespace uking::query
