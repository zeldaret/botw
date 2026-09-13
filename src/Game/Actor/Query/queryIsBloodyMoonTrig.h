#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsBloodyMoonTrig : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsBloodyMoonTrig, Query)
public:
    explicit IsBloodyMoonTrig(const InitArg& arg);
    ~IsBloodyMoonTrig() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
