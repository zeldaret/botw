#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckExtraEnergyOfPlayer : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckExtraEnergyOfPlayer, Query)
public:
    explicit CheckExtraEnergyOfPlayer(const InitArg& arg);
    ~CheckExtraEnergyOfPlayer() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
