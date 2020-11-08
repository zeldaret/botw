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

    bool applyResourceUpdate(const char* data, const char* data1);

    u32 getIdx() const { return mIdx; }
    const sead::SafeString& getId() const { return mId; }
    void setIndex(u32 idx) { mIdx = idx; }

protected:
    u32 mIdx = 0x1c;
    sead::FixedSafeString<128> mId;
};
KSYS_CHECK_SIZE_NX150(ParamIO, 0x278);

}  // namespace ksys
