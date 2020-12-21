#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDieCnt : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDieCnt, Query)
public:
    explicit CheckDieCnt(const InitArg& arg);
    ~CheckDieCnt() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
    sead::SafeString mActorName{};
};

}  // namespace uking::query
