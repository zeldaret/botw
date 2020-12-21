#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckNumOfBuyPicture : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckNumOfBuyPicture, Query)
public:
    explicit CheckNumOfBuyPicture(const InitArg& arg);
    ~CheckNumOfBuyPicture() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
