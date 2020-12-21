#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerEquip : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerEquip, Query)
public:
    explicit CheckPlayerEquip(const InitArg& arg);
    ~CheckPlayerEquip() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mPlayerEquipType{};
};

}  // namespace uking::query
