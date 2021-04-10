#pragma once

#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglResParameter.h>
#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::res {

class ASParamParser {
    SEAD_RTTI_BASE(ASParamParser)
public:
    struct ParseArgs {
        void* user_data;
        agl::utl::ResParameterList res_list;
        sead::Heap* heap;
    };

    virtual ~ASParamParser() = default;
    virtual bool parse(const ParseArgs& args) { return true; }

    agl::utl::ParameterList& getList() { return mList; }
    const agl::utl::ParameterList& getList() const { return mList; }

protected:
    u32 _8 = 8;
    agl::utl::ParameterList mList;
};
KSYS_CHECK_SIZE_NX150(ASParamParser, 0x58);

}  // namespace ksys::res
