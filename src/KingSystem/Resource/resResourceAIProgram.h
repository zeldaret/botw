#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {
enum class ActionType : int;
}

namespace ksys::res {

class AIProgram : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AIProgram, Resource)
public:
    struct Definition {
        const agl::utl::ParameterBase* findSInstParam(u32 name_hash) const;
        const agl::utl::ParameterBase* findSInstParam(const sead::SafeString& name) const;

        template <typename T>
        bool addSInstParam_(s32 idx, const char* name, sead::Heap* heap, const T& value);

        void finalize_();

        agl::utl::ParameterList mList;
        const char* mClassName;
        const char* mName;
        sead::Buffer<agl::utl::ParameterBase*> mSInstParams;
        agl::utl::ParameterObj mSInstObj;
    };
    KSYS_CHECK_SIZE_NX150(Definition, 0x98);

    struct AIActionDef : Definition {
        void finalize_();

        const char* mGroupName;
        sead::Buffer<u16> mChildIndices;
        sead::Buffer<u8> mBehaviorIndices;
        u16 mTriggerAction;
        u16 mDynamicParamChild;
        u16 _c4;
    };
    KSYS_CHECK_SIZE_NX150(AIActionDef, 0xc8);

    struct BehaviorDef : Definition {
        u16 mCalcTiming;
        u16 mNoStop;
    };
    KSYS_CHECK_SIZE_NX150(BehaviorDef, 0xa0);

    struct QueryDef : Definition {};
    KSYS_CHECK_SIZE_NX150(QueryDef, 0x98);

    AIProgram() : ParamIO("aiprog", 0) {}
    ~AIProgram() override;

    const sead::Buffer<AIActionDef>& getActionsOrAIs(act::ai::ActionType type) const;
    const sead::Buffer<BehaviorDef>& getBehaviors() const { return mBehaviors; }
    const sead::Buffer<QueryDef>& getQueries() const { return mQueries; }

    const AIActionDef& getAI(s32 index) const { return mAIs[index]; }
    const sead::Buffer<AIActionDef>& getAIs() const { return mAIs; }
    const sead::Buffer<AIActionDef>& getActions() const { return mActions; }

    const AIActionDef& getAction(act::ai::ActionType type, s32 index) const {
        return getActionsOrAIs(type)[index];
    }

    const sead::Buffer<u16>& getDemoAiActionIndices() const { return mDemoAIActionIndices; }
    const sead::Buffer<u8>& getDemoBehaviorIndices() const { return mDemoBehaviorIndices; }

    bool getSInstParam(const char** value, const Definition& def,
                       const sead::SafeString& param_name) const;
    bool getSInstParam(sead::SafeString* value, const Definition& def,
                       const sead::SafeString& param_name) const;
    bool getSInstParam(const s32** value, const Definition& def,
                       const sead::SafeString& param_name) const;
    bool getSInstParam(const f32** value, const Definition& def,
                       const sead::SafeString& param_name) const;
    bool getSInstParam(const sead::Vector3f** value, const Definition& def,
                       const sead::SafeString& param_name) const;
    bool getSInstParam(const bool** value, const Definition& def,
                       const sead::SafeString& param_name) const;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;
    bool needsParse() const override { return true; }

private:
    bool parse_(u8* data, size_t size, sead::Heap* parent_heap) override;
    bool parseAIActions(sead::Buffer<AIActionDef>& defs, sead::Heap* heap,
                        agl::utl::ParameterList& target_list,
                        const agl::utl::ResParameterList& root, const char* type_name);
    bool parseBehaviors(sead::Heap* heap, const agl::utl::ResParameterList& root);
    bool parseQueries(sead::Heap* heap, const agl::utl::ResParameterList& root);
    bool parseDefParams(Definition* def, void* buffer, sead::Heap* heap,
                        const agl::utl::ResParameterList& res, u16* param1, u16* param2);

    void finalize_() override;
    void finalizeAIActions(sead::Buffer<AIActionDef>& defs);
    void finalizeBehaviors();
    void finalizeQueries();

    template <typename T>
    bool getSInstParam_(const T** value, const Definition& def, const sead::SafeString& param_name,
                        agl::utl::ParameterType param_type, const T* default_value) const;

    sead::Heap* mHeap = nullptr;
    sead::SafeString mStr;

    sead::Buffer<AIActionDef> mAIs;
    sead::Buffer<AIActionDef> mActions;
    sead::Buffer<BehaviorDef> mBehaviors;
    sead::Buffer<QueryDef> mQueries;

    agl::utl::ParameterList mParamListAI;
    agl::utl::ParameterList mParamListAction;
    agl::utl::ParameterList mParamListBehavior;
    agl::utl::ParameterList mParamListQuery;

    sead::Buffer<u16> mDemoAIActionIndices;
    sead::Buffer<u8> mDemoBehaviorIndices;
};
KSYS_CHECK_SIZE_NX150(AIProgram, 0x448);

template <typename T>
inline bool AIProgram::getSInstParam_(const T** value, const AIProgram::Definition& def,
                                      const sead::SafeString& param_name,
                                      agl::utl::ParameterType param_type,
                                      const T* default_value) const {
    const auto* param = def.findSInstParam(param_name);
    if (!param || param->getParameterType() != param_type) {
        *value = default_value;
        return false;
    }
    *value = param->ptrT<T>();
    return true;
}

}  // namespace ksys::res
