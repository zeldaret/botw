#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace evfl {
class ParamAccessor;
struct QueryArg;
}  // namespace evfl

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

    bool getStaticParam(const f32** value, const sead::SafeString& param) const;

    bool getDynamicParam(sead::SafeString* value, const sead::SafeString& param) const;
    bool getDynamicParam(s32** value, const sead::SafeString& param) const;
    bool getDynamicParam(f32** value, const sead::SafeString& param) const;
    bool getDynamicParam(bool** value, const sead::SafeString& param) const;

    bool loadString(const evfl::ParamAccessor& accessor, const sead::SafeString& param);
    bool loadInt(const evfl::ParamAccessor& accessor, const sead::SafeString& param);
    bool loadFloat(const evfl::ParamAccessor& accessor, const sead::SafeString& param);
    bool loadBool(const evfl::ParamAccessor& accessor, const sead::SafeString& param);

    bool getAITreeVariable(sead::SafeString** value, const sead::SafeString& param) const;
    bool getAITreeVariable(void** value, const sead::SafeString& param) const;

    virtual bool hasPreDeleteCb() { return false; }
    virtual bool hasUpdateForPreDeleteCb() { return false; }
    virtual void m6() {}
    virtual bool init_(sead::Heap* heap) { return true; }
    virtual void loadParams() {}
    virtual int doQuery() { return 0; }
    virtual void loadParams(const evfl::QueryArg& arg) {}
    virtual bool updateForPreDelete() { return true; }
    virtual void onPreDelete() {}

protected:
    res::AIProgram* getAIProg() const;

    template <typename T>
    bool getDynamicParamImpl(T** value, const sead::SafeString& param, AIDefParamType type,
                             T* default_value) const {
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

struct QueryFactory {
    using CreateFn = Query* (*)(const Query::InitArg& arg, sead::Heap* heap);
    u32 hash;
    CreateFn create_fn;

    template <typename T>
    static Query* make(const Query::InitArg& arg, sead::Heap* heap) {
        return new (heap) T(arg);
    }
};

}  // namespace ksys::act::ai
