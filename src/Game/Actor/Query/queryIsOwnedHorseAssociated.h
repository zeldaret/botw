#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsOwnedHorseAssociated : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsOwnedHorseAssociated, Query)
public:
    explicit IsOwnedHorseAssociated(const InitArg& arg);
    ~IsOwnedHorseAssociated() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    bool* mIsRidden{};
};

}  // namespace uking::query
