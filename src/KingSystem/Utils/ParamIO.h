#pragma once

#include <agl/Utils/aglParameterIO.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class ParamIO : public agl::utl::IParameterIO, public sead::hostio::Node {
public:
    using agl::utl::IParameterIO::IParameterIO;

    virtual bool ParamIO_m0() { return false; }

protected:
    u32 _1d8 = 0x1c;
    sead::FixedSafeString<128> _1e0;
};
KSYS_CHECK_SIZE_NX150(ParamIO, 0x278);

}  // namespace ksys
