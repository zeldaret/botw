#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckGameDataInt : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckGameDataInt, Query)
public:
    explicit CheckGameDataInt(const InitArg& arg);
    ~CheckGameDataInt() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mValue{};
    sead::SafeString mGameDataIntName{};
    sead::SafeString mOperator{};
};

}  // namespace uking::query
