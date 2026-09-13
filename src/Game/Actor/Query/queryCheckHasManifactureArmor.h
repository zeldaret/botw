#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckHasManifactureArmor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckHasManifactureArmor, Query)
public:
    explicit CheckHasManifactureArmor(const InitArg& arg);
    ~CheckHasManifactureArmor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
