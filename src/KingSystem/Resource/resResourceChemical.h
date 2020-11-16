#pragma once

#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// TODO
class Chemical : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Chemical, Resource)
};

}  // namespace ksys::res
