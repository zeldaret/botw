#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class AISchedule : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AISchedule, Resource)
public:
    AISchedule() : ParamIO("baischedule", 0) {}

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return false; }

    u8* getData() const { return mData; }

private:
    u8* mData{};
};

}  // namespace ksys::res
