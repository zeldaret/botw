#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckEquipItemType : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckEquipItemType, Query)
public:
    explicit CheckEquipItemType(const InitArg& arg);
    ~CheckEquipItemType() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mCheckTargetActorName{};
};

}  // namespace uking::query
