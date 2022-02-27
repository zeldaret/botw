#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actASSetting.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"
#include "KingSystem/Resource/Actor/resResourceAISchedule.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include "KingSystem/Resource/Actor/resResourceAnimInfo.h"
#include "KingSystem/Resource/Actor/resResourceAttClient.h"
#include "KingSystem/Resource/Actor/resResourceAwareness.h"
#include "KingSystem/Resource/Actor/resResourceBoneControl.h"
#include "KingSystem/Resource/Actor/resResourceChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/Actor/resResourceLifeCondition.h"
#include "KingSystem/Resource/Actor/resResourceLod.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include "KingSystem/Resource/Actor/resResourcePhysics.h"
#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfig.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfigList.h"
#include "KingSystem/Resource/Actor/resResourceRecipe.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"
#include "KingSystem/Resource/Actor/resResourceUMii.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceArchive.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorParamMgr)

using Type = ActorParam::ResourceType;
using User = res::ActorLink::User;

ActorParamMgr::ActorParamMgr() = default;

void ActorParamMgr::init(sead::Heap* heap, sead::Heap* debug_heap) {
    mTempHeap = util::DualHeap::create(0x300000, "TmpActorParamMgr", heap, debug_heap,
                                       sizeof(void*), sead::Heap::cHeapDirection_Forward, false);
    mTempHeap->enableLock(true);
    mDebugHeap = debug_heap;

    mParams = new (mTempHeap) ActorParam[NumParams];

    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::ActorLink>(1.0, 0x1000),
                              "bxml");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::GParamList>(
                                  1.0, res::GParamList::getResourceFactoryFallbackSize() + 0x800),
                              "bgparamlist");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::ModelList>(2.0), "bmodellist");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::ASList>(0.0, 0x80000),
                              "baslist");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AIProgram>(1.0, 0x300000),
                              "baiprog");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Physics>(6.0), "bphysics");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Chemical>(0.0, 0x2000),
                              "bchemical");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AS>(0.0, 0x80000), "bas");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AttClientList>(1.0, 0x2000),
                              "batcllist");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AttClient>(1.0, 0x2000),
                              "batcl");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AISchedule>(1.0, 0x800),
                              "baischedule");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::DamageParam>(1.0, 0x20000),
                              "bdmgparam");
    res::registerEntryFactory(
        new (mTempHeap) res::EntryFactory<res::RagdollConfigList>(1.0, 0x2000), "brgconfiglist");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::RagdollConfig>(1.0, 0x20000),
                              "brgconfig");
    res::registerEntryFactory(
        new (mTempHeap) res::EntryFactory<res::RagdollBlendWeight>(1.0, 0x20000), "brgbw");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Awareness>, "bawareness");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Drop>(1.0, 0x5000), "bdrop");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Shop>(1.0, 0x20000), "bshop");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Recipe>(1.0, 0x20000),
                              "brecipe");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::Lod>(1.0, 0x20000), "blod");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::BoneControl>(1.0, 0x40000),
                              "bbonectrl");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::LifeCondition>(1.0, 0x20000),
                              "blifecondition");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::UMii>, "bumii");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::AnimInfo>(1.5), "baniminfo");
    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<sead::DirectResource>, "byaml");

    {
        using ResType = ActorParam::ResourceType;
        res::LoadRequest req;
        req.mRequester = "tapActorParamMgr";

        getDummyResHandle(ResType::AIProgram).load("Actor/AIProgram/Dummy.baiprog", &req);
        getDummyResHandle(ResType::ASList).load("Actor/ASList/Dummy.baslist", &req);
        getDummyResHandle(ResType::AttClientList).load("Actor/AttClientList/Dummy.batcllist", &req);
        getDummyResHandle(ResType::ModelList).load("Actor/ModelList/Dummy.bmodellist", &req);
        getDummyResHandle(ResType::Physics).load("Actor/Physics/Dummy.bphysics", &req);
        getDummyResHandle(ResType::Chemical).load("Actor/Chemical/Dummy.bchemical", &req);
        getDummyResHandle(ResType::AISchedule).load("Actor/AISchedule/Dummy.baischedule", &req);
        getDummyResHandle(ResType::EventFlow).load("EventFlow/Dummy.bfevfl", &req);
        getDummyResHandle(ResType::AS).load("Actor/AS/Dummy.bas", &req);
        getDummyResHandle(ResType::AttClient).load("Actor/AttClient/Dummy.batcl", &req);
        getDummyResHandle(ResType::DamageParam).load("Actor/DamageParam/Dummy.bdmgparam", &req);
        getDummyResHandle(ResType::RagdollConfigList)
            .load("Actor/RagdollConfigList/Dummy.brgconfiglist", &req);
        getDummyResHandle(ResType::RagdollConfig).load("Actor/RagdollConfig/Dummy.brgconfig", &req);
        getDummyResHandle(ResType::RagdollBlendWeight)
            .load("Actor/RagdollBlendWeight/Dummy.brgbw", &req);
        getDummyResHandle(ResType::Awareness).load("Actor/Awareness/Dummy.bawareness", &req);
        getDummyResHandle(ResType::DropTable).load("Actor/DropTable/Dummy.bdrop", &req);
        getDummyResHandle(ResType::ShopData).load("Actor/ShopData/Dummy.bshop", &req);
        getDummyResHandle(ResType::Recipe).load("Actor/Recipe/Dummy.brecipe", &req);
        getDummyResHandle(ResType::Lod).load("Actor/LOD/Dummy.blod", &req);
        getDummyResHandle(ResType::BoneControl).load("Actor/BoneControl/Dummy.bbonectrl", &req);
        getDummyResHandle(ResType::LifeCondition)
            .load("Actor/LifeCondition/Dummy.blifecondition", &req);
        getDummyResHandle(ResType::UMii).load("Actor/UMii/Dummy.bumii", &req);
        getDummyResHandle(ResType::AnimationInfo).load("Actor/AnimationInfo/Dummy.baniminfo", &req);

        auto* dummy_gparam_factory = new (mTempHeap) res::EntryFactory<res::DummyGParamList>(
            1.0, res::GParamList::getResourceFactoryFallbackSize() + 0x1400);
        req.mEntryFactory = dummy_gparam_factory;
        getDummyResHandle(ResType::GParamList)
            .load("Actor/GeneralParamList/Dummy.bgparamlist", &req);
        if (dummy_gparam_factory)
            delete dummy_gparam_factory;

        auto* modellist = static_cast<res::ModelList*>(
            getDummyResHandle(ResType::ModelList).getResourceUnchecked());
        modellist->markAsDummy();
    }

    res::registerEntryFactory(new (mTempHeap) res::EntryFactory<res::ASSetting>(0.0, 0x80000),
                              "bassetting");
    ASSetting::createInstance(mTempHeap);
    ASSetting::instance()->init("Actor/ASSetting.bassetting", mTempHeap);
    ActorParam::resetDummyResources();
}

ActorParamMgr::~ActorParamMgr() {
    ASSetting::deleteInstance();
}

bool ActorParamMgr::checkPath(const sead::SafeString& path) const {
    return res::returnFalse3(path);
}

ActorParam* ActorParamMgr::allocParam(const char* actor_name, bool* allocated_new) {
    auto lock = sead::makeScopedLock(mCS);

    ActorParam* free_param = nullptr;
    auto* param = getParam(actor_name, &free_param);

    if (!param) {
        param = free_param;
        if (free_param)
            free_param->mRes = {};
        else
            param = &mParams[NumParams - 1];

        param->mActorName = actor_name;
        *allocated_new = true;
    }

    param->incrementRef();
    return param;
}

// NON_MATCHING: addressing mode
ActorParam* ActorParamMgr::getParam(const char* actor_name, ActorParam** out_free_param) const {
    auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < NumParams; ++i) {
        auto* param = &mParams[i];
        if (param->getActorName().isEmpty()) {
            if (out_free_param && !*out_free_param)
                *out_free_param = param;
        } else if (param->getActorName() == actor_name) {
            return param;
        }
    }
    return nullptr;
}

ActorParam* ActorParamMgr::loadParam(const char* actor_name, res::Handle* pack_handle, void* x,
                                     u32 load_req_c) {
    bool allocated_new = false;
    ActorParam* param = allocParam(actor_name, &allocated_new);

    if (allocated_new) {
        loadFiles(param, mTempHeap, pack_handle, x, load_req_c);
        param->setEventSignal();
    } else {
        param->waitForEvent();
    }

    return param;
}

void ActorParamMgr::loadFiles(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle,
                              void* x, u32 load_req_c) {
    param->deleteResHandles();
    param->allocResHandles(heap, 0, ActorParam::NumResourceTypes + 1);
    param->mActiveBufferIdx = 0;

    const auto* link =
        loadFile<res::ActorLink>(param, Type::ActorLink, "Actor/ActorLink", "xml",
                                 param->getActorName().cstr(), pack_handle, x, load_req_c);

    if (link)
        param->setProfileAndPriority(link->getUserName(User::Profile), link->getPriority().cstr());

    const auto* actor_link = param->getRes().mActorLink;
    if (!actor_link)
        return;

    param->mActiveBufferIdx = 0;

    loadFile<res::ModelList>(param, Type::ModelList, "Actor/ModelList", "modellist",
                             actor_link->getUserName(User::Model), pack_handle, x, load_req_c);

    loadFile<res::UMii>(param, Type::UMii, "Actor/UMii", "umii",
                        actor_link->getUserName(User::UMii), pack_handle, x, load_req_c);

    loadFile<res::ASList>(param, Type::ASList, "Actor/ASList", "aslist",
                          actor_link->getUserName(res::ActorLink::User::AS), pack_handle, x,
                          load_req_c);

    loadFilesStep2(param, heap, pack_handle, x, load_req_c);
}

bool ActorParamMgr::requestLoadActorPack(res::Handle* handle, const sead::SafeString& actor_name,
                                         u32 load_req_c) {
    sead::FixedSafeString<128> path;
    res::LoadRequest req;

    if (mFlags.isOn(Flag::_5))
        return false;

    path.format("Actor/Pack/%s.bactorpack", actor_name.cstr());
    req.mRequester = actor_name;
    req._c = load_req_c;
    req._8 = true;
    req._28 = false;
    return handle->requestLoad(path, &req);
}

ActorParam* ActorParamMgr::loadParamAsync(const char* actor_name, res::Handle* pack_handle,
                                          bool* allocated_new, void* x, u32 load_req_c) {
    auto* param = allocParam(actor_name, allocated_new);
    if (!*allocated_new)
        return param;

    param->deleteResHandles();
    param->allocResHandles(mTempHeap, 0, ActorParam::NumResourceTypes + 1);
    param->mActiveBufferIdx = 0;

    loadFileAsync<res::ActorLink>(param, Type::ActorLink, "Actor/ActorLink", "xml",
                                  param->getActorName().cstr(), pack_handle, x, load_req_c);
    return param;
}

template <typename T>
bool ActorParamMgr::loadFileAsync(ActorParam* param, ActorParam::ResourceType type,
                                  const sead::SafeString& dir_name,
                                  const sead::SafeString& extension, const sead::SafeString& name,
                                  res::Handle* pack_handle, void* x, u32 load_req_c) {
    auto* handle = param->allocHandle();

    if (name != "Dummy" && !name.isEmpty()) {
        sead::FixedSafeString<128> path;
        res::LoadRequest req;
        prepareLoadFromActorPack(&path, &req, x, dir_name, extension, name, pack_handle, load_req_c,
                                 param->getActorName());
        return handle->requestLoad(path, &req);
    }

    if (ActorParam::isValidType(type)) {
        auto* res = sead::DynamicCast<T>(mDummyResources[u32(type)].getResource());
        param->setResource(type, res);
    }

    return true;
}

// NON_MATCHING: different address calculation for static_cast<ParamIO*>(res)->getPath()
template <typename T>
T* ActorParamMgr::handleAsyncFileLoad(ActorParam* param, s32* idx, ActorParam::ResourceType type,
                                      void*) {
    const s32 current_idx = *idx;
    auto& handle = param->mHandles[param->mActiveBufferIdx][current_idx];
    *idx = current_idx + 1;

    if (ActorParam::isValidType(type)) {
        if (auto* res = static_cast<T*>(param->getRes().mArray[u32(type)]))
            return res;
    }

    if (handle.hasParsedResource())
        return sead::DynamicCast<T>(handle.getResource());

    if (!handle.isReadyOrNeedsParse())
        return nullptr;

    handle.parseResource(nullptr);

    if (handle.checkLoadStatus() && type != Type::EventFlow)
        param->_a = 1;

    auto* res = sead::DynamicCast<T>(handle.getResource());
    if (res) {
        auto* unit = handle.getUnit();
        if (unit)
            static_cast<ParamIO*>(res)->getPath().copy(unit->getPath());
    } else {
        res = sead::DynamicCast<T>(mDummyResources[s32(type)].getResource());
    }

    if (ActorParam::isValidType(type) && res)
        param->setResource(type, res);

    return res;
}

bool ActorParamMgr::finishLoadingActorLink(ActorParam* param, void* x) {
    s32 idx = 0;
    if (!handleAsyncFileLoad<res::ActorLink>(param, &idx, Type::ActorLink, x))
        return param->_a != 0;

    const auto* link = param->getRes().mActorLink;
    if (!link)
        return true;

    param->setProfileAndPriority(link->getUsers().getProfile(), link->getPriority().cstr());
    return true;
}

void ActorParamMgr::loadParamAsyncStep2(ActorParam* param, res::Handle* pack_handle, void* x,
                                        u32 load_req_c) {
    const auto* link = param->getRes().mActorLink;

    loadFileAsync<res::ModelList>(param, Type::ModelList, "Actor/ModelList", "modellist",
                                  link->getUsers().getModel(), pack_handle, x, load_req_c);

    loadFileAsync<res::UMii>(param, Type::UMii, "Actor/UMii", "umii", link->getUsers().getUMii(),
                             pack_handle, x, load_req_c);

    loadFileAsync<res::ASList>(param, Type::ASList, "Actor/ASList", "aslist",
                               link->getUsers().getAS(), pack_handle, x, load_req_c);

    loadFileAsync<res::AttClientList>(param, Type::AttClientList, "Actor/AttClientList", "atcllist",
                                      link->getUserName(User::Attention), pack_handle, x,
                                      load_req_c);

    loadFileAsync<res::RagdollConfigList>(param, Type::RagdollConfigList, "Actor/RagdollConfigList",
                                          "rgconfiglist", link->getUserName(User::RgConfigList),
                                          pack_handle, x, load_req_c);

    loadFileAsync<res::AIProgram>(param, Type::AIProgram, "Actor/AIProgram", "aiprog",
                                  link->getUsers().getAIProgram(), pack_handle, x, load_req_c);

    loadFileAsync<res::GParamList>(param, Type::GParamList, "Actor/GeneralParamList", "gparamlist",
                                   link->getUsers().getGParam(), pack_handle, x, load_req_c);

    loadFileAsync<res::Physics>(param, Type::Physics, "Actor/Physics", "physics",
                                link->getUsers().getPhysics(), pack_handle, x, load_req_c);

    loadFileAsync<res::Chemical>(param, Type::Chemical, "Actor/Chemical", "chemical",
                                 link->getUsers().getChemical(), pack_handle, x, load_req_c);

    loadFileAsync<res::DamageParam>(param, Type::DamageParam, "Actor/DamageParam", "dmgparam",
                                    link->getUsers().getDamageParam(), pack_handle, x, load_req_c);

    loadFileAsync<res::RagdollBlendWeight>(
        param, Type::RagdollBlendWeight, "Actor/RagdollBlendWeight", "rgbw",
        link->getUsers().getRgBlendWeight(), pack_handle, x, load_req_c);

    loadFileAsync<res::Awareness>(param, Type::Awareness, "Actor/Awareness", "awareness",
                                  link->getUsers().getAwareness(), pack_handle, x, load_req_c);

    loadFileAsync<res::Drop>(param, Type::DropTable, "Actor/DropTable", "drop",
                             link->getUsers().getDropTable(), pack_handle, x, load_req_c);

    loadFileAsync<res::Shop>(param, Type::ShopData, "Actor/ShopData", "shop",
                             link->getUsers().getShopData(), pack_handle, x, load_req_c);

    loadFileAsync<res::Recipe>(param, Type::Recipe, "Actor/Recipe", "recipe",
                               link->getUsers().getRecipe(), pack_handle, x, load_req_c);

    loadFileAsync<res::Lod>(param, Type::Lod, "Actor/LOD", "lod", link->getUsers().getLOD(),
                            pack_handle, x, load_req_c);

    loadFileAsync<res::AISchedule>(param, Type::AISchedule, "Actor/AISchedule", "aischedule",
                                   link->getUsers().getAISchedule(), pack_handle, x, load_req_c);

    loadFileAsync<res::BoneControl>(param, Type::BoneControl, "Actor/BoneControl", "bonectrl",
                                    link->getUsers().getBoneControl(), pack_handle, x, load_req_c);

    loadFileAsync<res::LifeCondition>(param, Type::LifeCondition, "Actor/LifeCondition",
                                      "lifecondition", link->getUsers().getLifeCondition(),
                                      pack_handle, x, load_req_c);

    loadFileAsync<res::AnimInfo>(param, Type::AnimationInfo, "Actor/AnimationInfo", "animinfo",
                                 link->getUsers().getAnimationInfo(), pack_handle, x, load_req_c);
}

bool ActorParamMgr::finishLoadingStep2(ActorParam* param, void* x) {
    s32 idx = 1;

    if (!handleAsyncFileLoad<res::ModelList>(param, &idx, Type::ModelList, x))
        return false;

    if (!handleAsyncFileLoad<res::UMii>(param, &idx, Type::UMii, x))
        return false;

    if (!handleAsyncFileLoad<res::ASList>(param, &idx, Type::ASList, x))
        return false;

    if (!handleAsyncFileLoad<res::AttClientList>(param, &idx, Type::AttClientList, x))
        return false;

    if (!handleAsyncFileLoad<res::RagdollConfigList>(param, &idx, Type::RagdollConfigList, x))
        return false;

    if (!handleAsyncFileLoad<res::AIProgram>(param, &idx, Type::AIProgram, x))
        return false;

    if (!handleAsyncFileLoad<res::GParamList>(param, &idx, Type::GParamList, x))
        return false;

    if (!handleAsyncFileLoad<res::Physics>(param, &idx, Type::Physics, x))
        return false;

    if (!handleAsyncFileLoad<res::Chemical>(param, &idx, Type::Chemical, x))
        return false;

    if (!handleAsyncFileLoad<res::DamageParam>(param, &idx, Type::DamageParam, x))
        return false;

    if (!handleAsyncFileLoad<res::RagdollBlendWeight>(param, &idx, Type::RagdollBlendWeight, x))
        return false;

    if (!handleAsyncFileLoad<res::Awareness>(param, &idx, Type::Awareness, x))
        return false;

    if (!handleAsyncFileLoad<res::Drop>(param, &idx, Type::DropTable, x))
        return false;

    if (!handleAsyncFileLoad<res::Shop>(param, &idx, Type::ShopData, x))
        return false;

    if (!handleAsyncFileLoad<res::Recipe>(param, &idx, Type::Recipe, x))
        return false;

    if (!handleAsyncFileLoad<res::Lod>(param, &idx, Type::Lod, x))
        return false;

    if (!handleAsyncFileLoad<res::AISchedule>(param, &idx, Type::AISchedule, x))
        return false;

    if (!handleAsyncFileLoad<res::BoneControl>(param, &idx, Type::BoneControl, x))
        return false;

    if (!handleAsyncFileLoad<res::LifeCondition>(param, &idx, Type::LifeCondition, x))
        return false;

    if (!handleAsyncFileLoad<res::AnimInfo>(param, &idx, Type::AnimationInfo, x))
        return false;

    return true;
}

void ActorParamMgr::loadExtraResAsync(ActorParam* param, res::Handle* pack_handle, void* x,
                                      u32 load_req_c) {
    const auto* aslist = param->getRes().mASList;
    const auto* atcllist = param->getRes().mAttClientList;
    const auto* rgconfiglist = param->getRes().mRagdollConfigList;

    const auto num_as = aslist ? aslist->getASDefines().size() : 0;
    const auto num_att = atcllist ? atcllist->getClients().size() : 0;
    const auto num_rg = rgconfiglist ? rgconfiglist->getImpulseParams().size() : 0;

    param->allocResHandles(mTempHeap, 1, num_as + num_att + num_rg);
    param->mActiveBufferIdx = 1;

    if (aslist) {
        for (s32 i = 0; i < num_as; ++i) {
            loadFileAsync<res::AS>(param, Type::AS, "Actor/AS", "as",
                                   aslist->getASDefines()[i].getFileName(), pack_handle, x,
                                   load_req_c);
        }
    }

    if (atcllist) {
        for (s32 i = 0; i < num_att; ++i) {
            loadFileAsync<res::AttClient>(param, Type::AttClient, "Actor/AttClient", "atcl",
                                          atcllist->getClients()[i].getFileName(), pack_handle, x,
                                          load_req_c);
        }
    }

    if (rgconfiglist) {
        for (s32 i = 0; i < num_rg; ++i) {
            loadFileAsync<res::RagdollConfig>(
                param, Type::RagdollConfig, "Actor/RagdollConfig", "rgconfig",
                rgconfiglist->getImpulseParams()[i].getFileName(), pack_handle, x, load_req_c);
        }
    }
}

bool ActorParamMgr::finishLoadingExtraRes(ActorParam* param, void* x) {
    s32 idx = 0;

    auto* aslist = param->getRes().mASList;
    if (aslist) {
        for (s32 i = 0, n = aslist->getASDefines().size(); i < n; ++i) {
            const sead::SafeString file_name = aslist->getASDefines()[i].getFileName();
            if (file_name == "Dummy" || file_name.isEmpty()) {
                auto* as = sead::DynamicCast<res::AS>(mDummyResources[u32(Type::AS)].getResource());
                as->setIndex(u32(Type::AS));
                aslist->addAS_(i, as);
                ++idx;
            } else {
                const res::Handle& handle = param->mHandles[1][idx];
                if (handle.hasParsedResource()) {
                    ++idx;
                    continue;
                }

                auto* as = handleAsyncFileLoad<res::AS>(param, &idx, Type::AS, x);
                if (!as)
                    return false;

                as->setIndex(u32(Type::AS));
                aslist->addAS_(i, as);
            }
        }
    }

    auto* atcllist = param->getRes().mAttClientList;
    if (atcllist) {
        for (s32 i = 0, n = atcllist->getClients().size(); i < n; ++i) {
            const sead::SafeString file_name = atcllist->getClients()[i].getFileName();
            if (file_name == "Dummy" || file_name.isEmpty()) {
                auto* res = sead::DynamicCast<res::AttClient>(
                    mDummyResources[u32(Type::AttClient)].getResource());
                /// @bug This should be Type::AttClient. Copy paste error?
                res->setIndex(u32(Type::AS));
                atcllist->addClient_(i, res);
                ++idx;
            } else {
                const res::Handle& handle = param->mHandles[1][idx];
                if (handle.hasParsedResource()) {
                    ++idx;
                    continue;
                }

                auto* res = handleAsyncFileLoad<res::AttClient>(param, &idx, Type::AttClient, x);
                if (!res)
                    return false;

                res->setIndex(u32(Type::AttClient));
                atcllist->addClient_(i, res);
            }
        }
    }

    auto* rgconfiglist = param->getRes().mRagdollConfigList;
    if (rgconfiglist) {
        for (s32 i = 0, n = rgconfiglist->getImpulseParams().size(); i < n; ++i) {
            const sead::SafeString file_name = rgconfiglist->getImpulseParams()[i].getFileName();
            if (file_name == "Dummy" || file_name.isEmpty()) {
                auto* res = sead::DynamicCast<res::RagdollConfig>(
                    mDummyResources[u32(Type::RagdollConfig)].getResource());
                res->setIndex(u32(Type::RagdollConfig));
                rgconfiglist->addImpulseParamConfig_(i, res);
                ++idx;
            } else {
                const res::Handle& handle = param->mHandles[1][idx];
                if (handle.hasParsedResource()) {
                    ++idx;
                    continue;
                }

                auto* res =
                    handleAsyncFileLoad<res::RagdollConfig>(param, &idx, Type::RagdollConfig, x);
                if (!res)
                    return false;

                res->setIndex(u32(Type::RagdollConfig));
                rgconfiglist->addImpulseParamConfig_(i, res);
            }
        }
    }

    param->_9 = 0;
    param->onLoadFinished(this);
    param->setEventSignal();
    return true;
}

void ActorParamMgr::allocExtraResHandles(ActorParam* param, sead::Heap* heap) const {
    s32 num_extra_handles = 0;

    auto* aslist = param->getRes().mASList;
    auto* atcllist = param->getRes().mAttClientList;
    auto* rgconfiglist = param->getRes().mRagdollConfigList;

    if (aslist)
        num_extra_handles += aslist->getASDefines().size();

    if (atcllist)
        num_extra_handles += atcllist->getClients().size();

    if (rgconfiglist)
        num_extra_handles += rgconfiglist->getImpulseParams().size();

    param->allocResHandles(heap, 1, num_extra_handles);
}

void ActorParamMgr::loadFilesStep2(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle,
                                   void* x, u32 load_req_c) {
    const auto* link = param->getRes().mActorLink;
    param->mActiveBufferIdx = 0;

    loadFile<res::AttClientList>(param, Type::AttClientList, "Actor/AttClientList", "atcllist",
                                 link->getUserName(User::Attention), pack_handle, x, load_req_c);

    loadFile<res::RagdollConfigList>(param, Type::RagdollConfigList, "Actor/RagdollConfigList",
                                     "rgconfiglist", link->getUserName(User::RgConfigList),
                                     pack_handle, x, load_req_c);

    // Start loading the extra ActorParam files.
    allocExtraResHandles(param, heap);
    param->mActiveBufferIdx = 1;

    if (auto* aslist = param->getRes().mASList) {
        for (s32 i = 0; i < aslist->getASDefines().size(); ++i) {
            auto* as = loadFile<res::AS>(param, Type::AS, "Actor/AS", "as",
                                         aslist->getASDefines()[i].getFileName(), pack_handle, x,
                                         load_req_c);
            if (as) {
                as->setIndex(u32(Type::AS));
                aslist->addAS_(i, as);
            }
        }
    }

    if (auto* list = param->getRes().mAttClientList) {
        for (s32 i = 0; i < list->getClients().size(); ++i) {
            auto* client = loadFile<res::AttClient>(param, Type::AttClient, "Actor/AttClient",
                                                    "atcl", list->getClients()[i].getFileName(),
                                                    pack_handle, x, load_req_c);
            if (client) {
                client->setIndex(u32(Type::AttClient));
                list->addClient_(i, client);
            }
        }
    }

    if (auto* list = param->getRes().mRagdollConfigList) {
        for (s32 i = 0; i < list->getImpulseParams().size(); ++i) {
            auto* config = loadFile<res::RagdollConfig>(
                param, Type::RagdollConfig, "Actor/RagdollConfig", "rgconfig",
                list->getImpulseParams()[i].getFileName(), pack_handle, x, load_req_c);
            if (config) {
                config->setIndex(u32(Type::RagdollConfig));
                list->addImpulseParamConfig_(i, config);
            }
        }
    }

    // We have now finished loading the extra ActorParam files.
    // Go back to using the main resource handle buffer.
    param->mActiveBufferIdx = 0;

    loadFile<res::AIProgram>(param, Type::AIProgram, "Actor/AIProgram", "aiprog",
                             link->getUsers().getAIProgram(), pack_handle, x, load_req_c);

    loadFile<res::GParamList>(param, Type::GParamList, "Actor/GeneralParamList", "gparamlist",
                              link->getUsers().getGParam(), pack_handle, x, load_req_c);

    loadFile<res::Physics>(param, Type::Physics, "Actor/Physics", "physics",
                           link->getUsers().getPhysics(), pack_handle, x, load_req_c);

    loadFile<res::Chemical>(param, Type::Chemical, "Actor/Chemical", "chemical",
                            link->getUsers().getChemical(), pack_handle, x, load_req_c);

    loadFile<res::DamageParam>(param, Type::DamageParam, "Actor/DamageParam", "dmgparam",
                               link->getUsers().getDamageParam(), pack_handle, x, load_req_c);

    loadFile<res::RagdollBlendWeight>(param, Type::RagdollBlendWeight, "Actor/RagdollBlendWeight",
                                      "rgbw", link->getUsers().getRgBlendWeight(), pack_handle, x,
                                      load_req_c);

    loadFile<res::Awareness>(param, Type::Awareness, "Actor/Awareness", "awareness",
                             link->getUsers().getAwareness(), pack_handle, x, load_req_c);

    loadFile<res::Drop>(param, Type::DropTable, "Actor/DropTable", "drop",
                        link->getUsers().getDropTable(), pack_handle, x, load_req_c);

    loadFile<res::Shop>(param, Type::ShopData, "Actor/ShopData", "shop",
                        link->getUsers().getShopData(), pack_handle, x, load_req_c);

    loadFile<res::Recipe>(param, Type::Recipe, "Actor/Recipe", "recipe",
                          link->getUsers().getRecipe(), pack_handle, x, load_req_c);

    loadFile<res::Lod>(param, Type::Lod, "Actor/LOD", "lod", link->getUsers().getLOD(), pack_handle,
                       x, load_req_c);

    loadFile<res::AISchedule>(param, Type::AISchedule, "Actor/AISchedule", "aischedule",
                              link->getUsers().getAISchedule(), pack_handle, x, load_req_c);

    loadFile<res::BoneControl>(param, Type::BoneControl, "Actor/BoneControl", "bonectrl",
                               link->getUsers().getBoneControl(), pack_handle, x, load_req_c);

    loadFile<res::LifeCondition>(param, Type::LifeCondition, "Actor/LifeCondition", "lifecondition",
                                 link->getUsers().getLifeCondition(), pack_handle, x, load_req_c);

    loadFile<res::AnimInfo>(param, Type::AnimationInfo, "Actor/AnimationInfo", "animinfo",
                            link->getUsers().getAnimationInfo(), pack_handle, x, load_req_c);

    param->_9 = 0;
    param->onLoadFinished(this);
}

void ActorParamMgr::unloadParam(ActorParam* param) {
    auto lock = sead::makeScopedLock(mCS);
    param->decrementRef();
}

bool ActorParamMgr::prepareLoadFromActorPack(sead::BufferedSafeString* path, res::LoadRequest* req,
                                             void*, const sead::SafeString& dir_name,
                                             const sead::SafeString& extension,
                                             const sead::SafeString& file_name,
                                             res::Handle* pack_handle, u32 load_req_c,
                                             const sead::SafeString& requester) {
    path->format("%s/%s.b%s", dir_name.cstr(), file_name.cstr(), extension.cstr());

    bool in_pack = false;
    if (pack_handle && pack_handle->isSuccess()) {
        auto* pack = static_cast<sead::ArchiveRes*>(pack_handle->getResourceUnchecked());
        in_pack = pack->getFile(*path) != nullptr;
    }

    const bool cond1 = res::returnFalse3(*path);
    const bool is_host_path = res::isHostPath(*path);
    if (!in_pack && !cond1 && !is_host_path && path->include("bxml")) {
        sead::FormatFixedSafeString<256> message("↓↓↓\nファイルパス : %s\n↑↑↑\n", path->cstr());
        util::PrintDebug(message);
    }

    const bool ret = res::returnFalse3(*path);
    if (!ret && pack_handle && pack_handle->isSuccess()) {
        req->mPackHandle = pack_handle;
        req->_24 = false;
    }

    req->_c = load_req_c;
    req->mRequester = requester;
    req->_8 = true;
    return ret;
}

res::Archive* ActorParamMgr::loadActorPack(res::Handle* handle, const sead::SafeString& actor_name,
                                           u32 load_req_c) {
    sead::FixedSafeString<128> path;
    res::TempResourceLoader::LoadArg arg;
    arg.retry_on_failure = true;
    arg.use_handle = true;

    if (mFlags.isOn(Flag::_5))
        return nullptr;

    path.format("Actor/Pack/%s.bactorpack", actor_name.cstr());
    arg.load_req.mRequester = actor_name;
    arg.load_req._c = load_req_c;
    arg.load_req._8 = true;
    arg.load_req._28 = false;
    arg.load_req.mPath = path;

    res::TempResourceLoader loader;
    {
        res::TempResourceLoader::InitArg init_arg{};
        res::ResourceMgrTask::instance()->initTempResourceLoader(&loader, init_arg);
    }
    loader.load(arg);

    res::SimpleLoadRequest req;
    req.mRequester = "tap::ActorParamMgr";
    req.mPath = path;
    req._c = 2;
    return sead::DynamicCast<res::Archive>(handle->load(path, &req));
}

template <typename T>
T* ActorParamMgr::loadFile(ActorParam* param, ActorParam::ResourceType type, const char* dir_name_c,
                           const char* extension_c, const char* name_c, res::Handle* pack_handle,
                           void* x, u32 load_req_c) {
    const sead::SafeString name = name_c;
    const sead::SafeString extension = extension_c;
    sead::FixedSafeString<128> path;

    T* res = nullptr;

    if (name != "Dummy" && !name.isEmpty()) {
        auto* temp_handle = param->allocHandle();
        const sead::SafeString* actor_name;
        path.format("%s/%s.b%s", dir_name_c, name_c, extension_c);
        {
            res::SimpleLoadRequest req;
            req._8 = true;
            actor_name = &param->getActorName();
            req.mRequester = *actor_name;
            req.mPath = path;
            req._c = 2;
            res = sead::DynamicCast<T>(temp_handle->load(path, &req));
        }

        // If loading the resource from the RomFS has failed, try to load it from the actor pack.
        if (!res) {
            if (!pack_handle->isSuccess())
                loadActorPack(pack_handle, *actor_name, load_req_c);

            res::LoadRequest req;
            prepareLoadFromActorPack(&path, &req, x, dir_name_c, extension_c, name_c, pack_handle,
                                     load_req_c, *actor_name);
            res = sead::DynamicCast<T>(temp_handle->load(path, &req));

            if (!res) {
                static_cast<void>(temp_handle->isSuccess());
                // Try again without the pack.
                if (req.mPackHandle) {
                    req.mPackHandle = nullptr;
                    req._24 = false;
                    res = sead::DynamicCast<T>(temp_handle->load(path, &req));
                    if (!res)
                        static_cast<void>(temp_handle->isSuccess());
                }
            }
        }

        if (!res)
            param->freeLastHandle();
        else if (type == ActorParam::ResourceType::EventFlow)
            temp_handle->requestUnload2();

    } else {
        path.format("%s/%s.b%s", dir_name_c, name_c, extension_c);
        res = sead::DynamicCast<T>(mDummyResources[s32(type)].getResource());
    }

    if (res) {
        if (type == ActorParam::ResourceType::EventFlow)
            return res;

        static_cast<ParamIO*>(res)->getPath().copy(path);
        param->setResourceIfValidType(type, res);
        return res;
    }

    if (extension != "fevfl")
        param->_a = 1;

    // Fall back to using the dummy resource.
    res = sead::DynamicCast<T>(mDummyResources[s32(type)].getResource());
    sead::FixedSafeString<128> dummy_path;
    dummy_path.format("%s/Dummy.b%s", dir_name_c, extension_c);
    if (res) {
        static_cast<ParamIO*>(res)->getPath().copy(dummy_path);
        param->setResourceIfValidType(type, res);
    }

    return res;
}

void ActorParamMgr::syncData(char* data) {
    auto lock = sead::makeScopedLock(mCS);

    char* data1 = data;
    while (*data1++ != ' ')
        continue;
    data1[-1] = 0;

    while (*data1++ != '[')
        continue;

    char* data2 = data1;
    while (*data2++ != ']')
        continue;
    data2[-1] = 0;

    for (int i = 0; i < NumParams; ++i) {
        auto& param = mParams[i];
        if (param.getActorName().isEmpty())
            continue;

        param.waitForEvent();
        const int ret = param.updateResource(data, data1, data2);
        if (ret == 0)
            return;
        if (ret == 1) {
            sead::FixedSafeString<64> message;
            message.format("[UpdateResource]%s", data);
            log(message.cstr());
            return;
        }
    }
}

res::GParamList* ActorParamMgr::getDummyGParamList() const {
    return static_cast<res::GParamList*>(
        mDummyResources[u32(ActorParam::ResourceType::GParamList)].getResourceUnchecked());
}

}  // namespace ksys::act
