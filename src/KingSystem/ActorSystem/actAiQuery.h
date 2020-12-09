#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace evfl {
class ParamAccessor;
}

namespace ksys::act {
class Actor;
}

namespace ksys::res {
class AIProgram;
}

namespace ksys::act::ai {

class Query {
    SEAD_RTTI_BASE(Query)
public:
    struct InitArg {
        Actor* actor;
        /// The index of the query definition in the actor's AI program.
        s32 def_idx;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    explicit Query(const InitArg& arg);
    virtual ~Query() = default;

    bool init(sead::Heap* heap);
    const char* getName() const;

    bool getSInstParam(const f32** value, const sead::SafeString& param) const;

    bool getDInstParam(sead::SafeString* value, const sead::SafeString& param) const;
    bool getDInstParam(const s32** value, const sead::SafeString& param) const;
    bool getDInstParam(const f32** value, const sead::SafeString& param) const;
    bool getDInstParam(const bool** value, const sead::SafeString& param) const;

    bool loadString(evfl::ParamAccessor* accessor, const sead::SafeString& param);
    bool loadInt(evfl::ParamAccessor* accessor, const sead::SafeString& param);
    bool loadFloat(evfl::ParamAccessor* accessor, const sead::SafeString& param);
    bool loadBool(evfl::ParamAccessor* accessor, const sead::SafeString& param);

    bool getAITreeVariable(const sead::SafeString** value, const sead::SafeString& param) const;
    bool getAITreeVariable(const char** value, const sead::SafeString& param) const;

    virtual bool m4() { return false; }
    virtual bool m5() { return false; }
    virtual void m6() {}
    virtual bool init_(sead::Heap* heap) { return true; }
    virtual void loadParams() {}
    virtual int doQuery() { return 0; }
    virtual void m10() {}
    virtual bool m11() { return true; }
    virtual void m12() {}

protected:
    res::AIProgram* getAIProg() const;

    template <typename T>
    bool getDInstParam_(const T** value, const sead::SafeString& param, AIDefParamType type,
                        const T* default_value) const {
        *value = static_cast<T*>(mParamPack.getAITreeVariablePointer(param, type));
        if (*value)
            return true;
        *value = default_value;
        return false;
    }

    Actor* mActor;
    ParamPack mParamPack;
    s32 mDefIdx;
};
KSYS_CHECK_SIZE_NX150(Query, 0x20);

}  // namespace ksys::act::ai
