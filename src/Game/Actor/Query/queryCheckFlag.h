#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckFlag : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckFlag, Query)
public:
    explicit CheckFlag(const InitArg& arg);
    ~CheckFlag() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mFlagName{};
};

}  // namespace uking::query
