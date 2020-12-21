#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasSpecificArmorSeries : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasSpecificArmorSeries, Query)
public:
    explicit HasSpecificArmorSeries(const InitArg& arg);
    ~HasSpecificArmorSeries() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mSeriesType{};
};

}  // namespace uking::query
