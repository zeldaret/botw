#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckEquipArmorSeriesType : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckEquipArmorSeriesType, Query)
public:
    explicit CheckEquipArmorSeriesType(const InitArg& arg);
    ~CheckEquipArmorSeriesType() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    bool* mCheckHead{};
    bool* mCheckUpper{};
    bool* mCheckLower{};
    sead::SafeString mCheckType{};
};

}  // namespace uking::query
