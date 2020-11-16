#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class RagdollConfig : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(RagdollConfig, Resource)
};

}  // namespace ksys::res
