#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class RagdollBlendWeight : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(RagdollBlendWeight, Resource)
};

}  // namespace ksys::res
