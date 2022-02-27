#include "KingSystem/Resource/Actor/resResourceAIProgram.h"
#include <agl/Utils/aglParameter.h>
#include <heap/seadHeapMgr.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/Resource/resCurrentResNameMgr.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::res {

AIProgram::~AIProgram() = default;

const sead::Buffer<AIProgram::AIActionDef>&
AIProgram::getActionsOrAIs(act::ai::ActionType type) const {
    return type == act::ai::ActionType::AI ? mAIs : mActions;
}

void AIProgram::doCreate_(u8*, u32, sead::Heap*) {
    mStr = CurrentResNameMgr::instance()->getCurrentResName();
}

static bool parseAIActionIdx(agl::utl::ResParameterObj obj, sead::Buffer<u16>& buffer,
                             sead::Heap* heap, bool clear = false) {
    if (obj.ptr() == nullptr)
        return true;

    const auto num = obj.getNum();
    if (num == 0)
        return true;

    if (!buffer.tryAllocBuffer(num, heap))
        return false;

    if (clear) {
        for (s32 i = 0; i < num; ++i)
            buffer(i) = 0;
    }

    auto it = buffer.begin(), it_end = buffer.end();
    auto it_res = obj.begin(), it_res_end = obj.end();
    auto* res_ptr = it_res.getParam().ptr();
    for (; it != it_end && it_res != it_res_end; ++it, ++it_res)
        *it = *agl::utl::ResParameter{res_ptr + it.getIndex()}.getData<s32>();

    return true;
}

static bool parseBehaviorIdx(agl::utl::ResParameterObj obj, sead::Buffer<u8>& buffer,
                             sead::Heap* heap) {
    if (obj.ptr() == nullptr)
        return true;

    const auto num = obj.getNum();
    if (num == 0)
        return true;

    if (!buffer.tryAllocBuffer(num, heap))
        return false;

    for (s32 i = 0; i < num; ++i)
        buffer(i) = 0;

    auto it = buffer.begin(), it_end = buffer.end();
    auto it_res = obj.begin(), it_res_end = obj.end();
    for (; it != it_end && it_res != it_res_end; ++it, ++it_res)
        *it = *it_res.getParam().getData<s32>();

    return true;
}

// NON_MATCHING: the parameter iteration loops in parseAIActionIdx and parseBehaviorIdx
bool AIProgram::parse_(u8* data, size_t, sead::Heap* parent_heap) {
    if (data) {
        auto* heap = util::tryCreateDualHeap(parent_heap);
        mHeap = heap;
        if (!heap)
            return false;

        heap->enableWarning(false);
        heap = mHeap;

        agl::utl::ResParameterArchive archive{data};
        const auto root = archive.getRootList();

        if (!parseAIActions(mAIs, heap, mParamListAI, root, "AI") ||
            !parseAIActions(mActions, heap, mParamListAction, root, "Action") ||
            !parseBehaviors(heap, root) || !parseQueries(heap, root)) {
            return false;
        }

        const auto ai_idx_obj = agl::utl::getResParameterObj(root, "DemoAIActionIdx");
        if (!parseAIActionIdx(ai_idx_obj, mDemoAIActionIndices, heap)) {
            mHeap->adjust();
            return false;
        }

        const auto behavior_idx_obj = agl::utl::getResParameterObj(root, "DemoBehaviorIdx");
        if (!parseBehaviorIdx(behavior_idx_obj, mDemoBehaviorIndices, heap)) {
            mHeap->adjust();
            return false;
        }

        applyResParameterArchive(agl::utl::ResParameterArchive{data});
    }

    mHeap->adjust();
    return true;
}

// NON_MATCHING: the parameter iteration loops in parseAIActionIdx and parseBehaviorIdx
bool AIProgram::parseAIActions(sead::Buffer<AIActionDef>& defs, sead::Heap* heap,
                               agl::utl::ParameterList& target_list,
                               const agl::utl::ResParameterList& root, const char* type_name) {
    const auto list = agl::utl::getResParameterList(root, type_name);
    if (!list.ptr())
        return false;

    const auto num = list.getResParameterListNum();
    if (num == 0)
        return true;

    if (!defs.tryAllocBuffer(num, heap))
        return false;

    for (auto& action : defs) {
        action.mClassName = "";
        action.mName = "";
        action.mGroupName = "";
    }

    auto it_res = list.listBegin();
    const auto it_res_end = list.listEnd();

    sead::FixedSafeString<32> list_name{type_name};
    list_name.append("_");
    const s32 trim_length = list_name.calcLength();

    auto it = defs.begin();
    const auto it_end = defs.end();
    for (; it != it_end && it_res != it_res_end; ++it, ++it_res) {
        list_name.trim(trim_length);
        list_name.appendWithFormat("%d", it.getIndex());
        target_list.addList(&it->mList, list_name);

        const auto res = *it_res;
        const auto def_obj = agl::utl::getResParameterObj(res, "Def");
        if (def_obj.ptr()) {
            it->mName = agl::utl::getResParameter(def_obj, "Name").getData<char>();
            it->mClassName = agl::utl::getResParameter(def_obj, "ClassName").getData<char>();

            const auto group_name = agl::utl::getResParameter(def_obj, "GroupName");
            if (group_name.ptr())
                it->mGroupName = group_name.getData<char>();
            else
                it->mGroupName = "";
        }

        const auto child_idx_obj = agl::utl::getResParameterObj(res, "ChildIdx");
        if (!parseAIActionIdx(child_idx_obj, it->mChildIndices, heap, true))
            return false;

        const auto behavior_idx_obj = agl::utl::getResParameterObj(res, "BehaviorIdx");
        if (!parseBehaviorIdx(behavior_idx_obj, it->mBehaviorIndices, heap))
            return false;

        if (!parseDefParams(&*it, &defs, heap, res, &it->mTriggerAction, &it->mDynamicParamChild))
            return false;
    }

    addList(&target_list, type_name);
    return true;
}

bool AIProgram::parseBehaviors(sead::Heap* heap, const agl::utl::ResParameterList& root) {
    const auto list = agl::utl::getResParameterList(root, "Behavior");
    if (!list.ptr())
        return true;

    const auto num = list.getResParameterListNum();
    if (num == 0)
        return true;

    if (!mBehaviors.tryAllocBuffer(num, heap))
        return false;

    for (auto& behavior : mBehaviors) {
        behavior.mClassName = "";
        behavior.mName = "";
    }

    auto it_res = list.listBegin();
    const auto it_res_end = list.listEnd();

    sead::FixedSafeString<32> list_name{"Behavior_"};
    const s32 trim_length = list_name.calcLength();

    auto it = mBehaviors.begin();
    const auto it_end = mBehaviors.end();
    for (; it != it_end && it_res != it_res_end; ++it, ++it_res) {
        list_name.trim(trim_length);
        list_name.appendWithFormat("%d", it.getIndex());
        mParamListBehavior.addList(&it->mList, list_name);

        const auto res = *it_res;
        const auto obj = agl::utl::getResParameterObj(res, "Def");
        if (obj.ptr()) {
            const auto name_param = agl::utl::getResParameter(obj, "ClassName");
            it->mClassName = name_param.getData<char>();
        }

        if (!parseDefParams(&*it, &mBehaviors, heap, res, &it->mCalcTiming, &it->mNoStop))
            return false;
    }

    addList(&mParamListBehavior, "Behavior");
    return true;
}

bool AIProgram::parseQueries(sead::Heap* heap, const agl::utl::ResParameterList& root) {
    const auto list = agl::utl::getResParameterList(root, "Query");
    if (!list.ptr())
        return true;

    const auto num = list.getResParameterListNum();
    if (num == 0)
        return true;

    if (!mQueries.tryAllocBuffer(num, heap))
        return false;

    for (auto& query : mQueries) {
        query.mClassName = "";
        query.mName = "";
    }

    auto it_res = list.listBegin();
    const auto it_res_end = list.listEnd();

    sead::FixedSafeString<32> list_name{"Query_"};
    const s32 trim_length = list_name.calcLength();

    auto it = mQueries.begin();
    const auto it_end = mQueries.end();
    for (; it != it_end && it_res != it_res_end; ++it, ++it_res) {
        list_name.trim(trim_length);
        list_name.appendWithFormat("%d", it.getIndex());
        mParamListQuery.addList(&it->mList, list_name);

        const auto res = *it_res;
        const auto obj = agl::utl::getResParameterObj(res, "Def");
        if (obj.ptr()) {
            const auto name_param = agl::utl::getResParameter(obj, "ClassName");
            it->mClassName = name_param.getData<char>();
        }

        if (!parseDefParams(&*it, &mQueries, heap, res, nullptr, nullptr))
            return false;
    }

    addList(&mParamListQuery, "Query");
    return true;
}

void AIProgram::finalize_() {
    {
        sead::ScopedCurrentHeapSetter setter{mHeap};

        finalizeAIActions(mAIs);
        finalizeAIActions(mActions);
        finalizeBehaviors();
        finalizeQueries();
        mDemoBehaviorIndices.freeBuffer();
        mDemoAIActionIndices.freeBuffer();
    }

    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
}

void AIProgram::Definition::finalize_() {
    for (auto*& param : mSInstParams) {
        if (param) {
            delete param;
            param = nullptr;
        }
    }
    mSInstParams.freeBuffer();
}

void AIProgram::AIActionDef::finalize_() {
    Definition::finalize_();
    mChildIndices.freeBuffer();
    mBehaviorIndices.freeBuffer();
}

void AIProgram::finalizeAIActions(sead::Buffer<AIActionDef>& defs) {
    for (auto& def : defs)
        def.finalize_();
    defs.freeBuffer();
}

void AIProgram::finalizeBehaviors() {
    for (auto& def : mBehaviors)
        def.finalize_();
    mBehaviors.freeBuffer();
}

void AIProgram::finalizeQueries() {
    for (auto& def : mQueries)
        def.finalize_();
    mQueries.freeBuffer();
}

const agl::utl::ParameterBase* AIProgram::Definition::findSInstParam(u32 name_hash) const {
    for (const auto* param : mSInstParams) {
        if (param && param->getNameHash() == name_hash)
            return param;
    }
    return nullptr;
}

const agl::utl::ParameterBase*
AIProgram::Definition::findSInstParam(const sead::SafeString& name) const {
    return findSInstParam(agl::utl::ParameterBase::calcHash(name));
}

bool AIProgram::getSInstParam(const char** value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    const auto* param = def.findSInstParam(param_name);
    if (!param || param->getParameterType() != agl::utl::ParameterType::StringRef) {
        *value = &sead::SafeString::cNullChar;
        return false;
    }
    *value = param->ptrT<char>();
    return true;
}

bool AIProgram::getSInstParam(sead::SafeString* value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    const auto* param = def.findSInstParam(param_name);
    if (!param || param->getParameterType() != agl::utl::ParameterType::StringRef) {
        *value = sead::SafeString::cEmptyString;
        return false;
    }
    *value = param->ptrT<char>();
    return true;
}

bool AIProgram::getSInstParam(const s32** value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    static const s32 sDefault{};
    return getSInstParam_(value, def, param_name, agl::utl::ParameterType::Int, &sDefault);
}

bool AIProgram::getSInstParam(const f32** value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    static const f32 sDefault{};
    return getSInstParam_(value, def, param_name, agl::utl::ParameterType::F32, &sDefault);
}

bool AIProgram::getSInstParam(const sead::Vector3f** value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    return getSInstParam_(value, def, param_name, agl::utl::ParameterType::Vec3,
                          &sead::Vector3f::zero);
}

bool AIProgram::getSInstParam(const bool** value, const AIProgram::Definition& def,
                              const sead::SafeString& param_name) const {
    static const bool sDefault{};
    return getSInstParam_(value, def, param_name, agl::utl::ParameterType::Bool, &sDefault);
}

bool AIProgram::parseDefParams(AIProgram::Definition* def, void* buffer, sead::Heap* heap,
                               const agl::utl::ResParameterList& res, u16* param1, u16* param2) {
    const auto sinst_obj = agl::utl::getResParameterObj(res, "SInst");
    const s32 sinst_num_params = sinst_obj.ptr() ? sinst_obj.getNum() : 0;

    AIDef aidef;

    if (&mAIs == buffer) {
        AIClassDef::instance()->getDef(&aidef, def->mClassName, AIDefInstParamKind::Static,
                                       AIDefType::AI);
        *param1 = aidef.trigger_action;
        *param2 = aidef.dynamic_param_child;
    } else if (&mActions == buffer) {
        AIClassDef::instance()->getDef(&aidef, def->mClassName, AIDefInstParamKind::Static,
                                       AIDefType::Action);
        *param1 = aidef.trigger_action;
        *param2 = 0;
    } else if (&mBehaviors == buffer) {
        AIClassDef::instance()->getDef(&aidef, def->mClassName, AIDefInstParamKind::Static,
                                       AIDefType::Behavior);
        *param1 = u16(aidef.calc_timing);
        *param2 = aidef.no_stop;
    } else {
        AIClassDef::instance()->getDef(&aidef, def->mClassName, AIDefInstParamKind::Static,
                                       AIDefType::Query);
    }

    if (sinst_num_params != 0) {
        const auto num_params =
            aidef.num_params < sinst_num_params ? aidef.num_params : sinst_num_params;

        if (!def->mSInstParams.tryAllocBuffer(sinst_num_params, heap))
            return false;

        for (s32 i = 0; i < sinst_num_params; ++i)
            def->mSInstParams[i] = nullptr;

        for (s32 i = 0; i < num_params; ++i) {
            const char* name = aidef.param_names[i];
            switch (aidef.param_types[i]) {
            case AIDefParamType::String:
            case AIDefParamType::Tree:
                if (!def->addSInstParam_<sead::SafeString>(i, name, heap, ""))
                    return false;
                break;
            case AIDefParamType::UInt:
                if (!def->addSInstParam_<u32>(i, name, heap, 0))
                    return false;
                break;
            case AIDefParamType::Int:
                if (!def->addSInstParam_<s32>(i, name, heap, 0))
                    return false;
                break;
            case AIDefParamType::Float:
                if (!def->addSInstParam_<f32>(i, name, heap, 0))
                    return false;
                break;
            case AIDefParamType::Vec3:
                if (!def->addSInstParam_<sead::Vector3f>(i, name, heap, sead::Vector3f::zero))
                    return false;
                break;
            case AIDefParamType::Bool:
                if (!def->addSInstParam_<bool>(i, name, heap, false))
                    return false;
                break;
            default:
                def->mSInstParams[i] = nullptr;
                break;
            }
        }
    }

    def->mList.addObj(&def->mSInstObj, "SInst");
    return true;
}

template <typename T>
bool AIProgram::Definition::addSInstParam_(s32 idx, const char* name, sead::Heap* heap,
                                           const T& value) {
    mSInstParams[idx] = new (heap) agl::utl::Parameter<T>;

    auto* param = static_cast<agl::utl::Parameter<T>*>(mSInstParams[idx]);
    if (!param)
        return false;

    param->initializeParameter(value, name, name, &mSInstObj);
    return true;
}

}  // namespace ksys::res
