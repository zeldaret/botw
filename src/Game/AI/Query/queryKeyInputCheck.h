#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class KeyInputCheck : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(KeyInputCheck, Query)
public:
    explicit KeyInputCheck(const InitArg& arg);
    ~KeyInputCheck() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mValidInput{};
    u32 _28{};
    u32 _2c{};
};

}  // namespace uking::query
