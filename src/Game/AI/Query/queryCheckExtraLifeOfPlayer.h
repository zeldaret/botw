#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckExtraLifeOfPlayer : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckExtraLifeOfPlayer, Query)
public:
    explicit CheckExtraLifeOfPlayer(const InitArg& arg);
    ~CheckExtraLifeOfPlayer() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mThreshold{};
};

}  // namespace uking::query
