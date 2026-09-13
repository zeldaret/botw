#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckItemShopPorchVacancy : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckItemShopPorchVacancy, Query)
public:
    explicit CheckItemShopPorchVacancy(const InitArg& arg);
    ~CheckItemShopPorchVacancy() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
