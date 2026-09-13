#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsOffLinkTag : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsOffLinkTag, Query)
public:
    explicit IsOffLinkTag(const InitArg& arg);
    ~IsOffLinkTag() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mSignalType{};
};

}  // namespace uking::query
