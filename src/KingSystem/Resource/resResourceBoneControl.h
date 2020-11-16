#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class BoneControl : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(BoneControl, Resource)
};

}  // namespace ksys::res
