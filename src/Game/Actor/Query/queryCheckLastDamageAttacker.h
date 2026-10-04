#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckLastDamageAttacker : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckLastDamageAttacker, Query)
public:
    explicit CheckLastDamageAttacker(const InitArg& arg);
    ~CheckLastDamageAttacker() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mName{};
};

}  // namespace uking::query
