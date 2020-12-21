#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckHorseRegistered : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckHorseRegistered, Query)
public:
    explicit CheckHorseRegistered(const InitArg& arg);
    ~CheckHorseRegistered() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
