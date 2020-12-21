#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace ksys::act::ai {

class DummyQuery : public Query {
    SEAD_RTTI_OVERRIDE(DummyQuery, Query)
public:
    explicit DummyQuery(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void loadParams() override;
};

}  // namespace ksys::act::ai
