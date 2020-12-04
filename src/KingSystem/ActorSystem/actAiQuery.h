#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class BaseProc;
}

namespace ksys::act::ai {

class Query {
    SEAD_RTTI_BASE(Query)
public:
    struct InitArg {
        BaseProc* proc;
        /// The index of the query definition in the actor's AI program.
        s32 def_idx;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    explicit Query(const InitArg& arg);
    virtual ~Query() = default;

    virtual bool m4() { return false; }
    virtual bool m5() { return false; }
    virtual void m6() {}
    virtual bool m7() { return true; }
    virtual void m8() {}
    virtual int doQuery() { return 0; }
    virtual void m10() {}
    virtual bool m11() { return true; }
    virtual void m12() {}

protected:
    BaseProc* mProc;
    ParamPack mParamPack;
    s32 mDefIdx;
};
KSYS_CHECK_SIZE_NX150(Query, 0x20);

}  // namespace ksys::act::ai
