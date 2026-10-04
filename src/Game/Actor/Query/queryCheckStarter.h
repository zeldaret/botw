#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckStarter : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckStarter, Query)
public:
    explicit CheckStarter(const InitArg& arg);
    ~CheckStarter() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mActorName{};
    sead::SafeString mUniqueName{};
};

}  // namespace uking::query
