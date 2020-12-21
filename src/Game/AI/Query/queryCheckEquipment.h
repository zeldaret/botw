#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckEquipment : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckEquipment, Query)
public:
    explicit CheckEquipment(const InitArg& arg);
    ~CheckEquipment() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mEquipItemName{};
};

}  // namespace uking::query
