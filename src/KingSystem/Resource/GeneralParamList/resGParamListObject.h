#pragma once

#include <agl/Utils/aglParameterObj.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

/// Base class for GeneralParamList parameter objects.
/// @bug This should have a virtual destructor...
class GParamListObject : public sead::hostio::Node {
public:
    virtual const char* getName() const = 0;

protected:
    agl::utl::ParameterObj mObj;
};
KSYS_CHECK_SIZE_NX150(GParamListObject, 0x38);

}  // namespace ksys::res
