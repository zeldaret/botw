#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class AISchedule : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AISchedule, Resource)
};

}  // namespace ksys::res
