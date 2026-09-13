#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CanCreateMakeItemList : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CanCreateMakeItemList, Query)
public:
    explicit CanCreateMakeItemList(const InitArg& arg);
    ~CanCreateMakeItemList() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mShopType{};
    bool* mIncludePorchMainMat{};
    bool* mIncludePorchSubMat{};
};

}  // namespace uking::query
