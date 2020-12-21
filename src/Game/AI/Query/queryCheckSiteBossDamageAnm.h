#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckSiteBossDamageAnm : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckSiteBossDamageAnm, Query)
public:
    explicit CheckSiteBossDamageAnm(const InitArg& arg);
    ~CheckSiteBossDamageAnm() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
