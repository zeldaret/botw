#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class Physics : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Physics, Resource)
};

}  // namespace ksys::res
