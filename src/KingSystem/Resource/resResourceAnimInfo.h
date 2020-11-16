#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class AnimInfo : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AnimInfo, Resource)
};

}  // namespace ksys::res
