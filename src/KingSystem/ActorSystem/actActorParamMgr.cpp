#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actASSetting.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceAIProgram.h"
#include "KingSystem/Resource/resResourceAISchedule.h"
#include "KingSystem/Resource/resResourceAS.h"
#include "KingSystem/Resource/resResourceASList.h"
#include "KingSystem/Resource/resResourceActorLink.h"
#include "KingSystem/Resource/resResourceAnimInfo.h"
#include "KingSystem/Resource/resResourceArchive.h"
#include "KingSystem/Resource/resResourceAttClient.h"
#include "KingSystem/Resource/resResourceAttClientList.h"
#include "KingSystem/Resource/resResourceAwareness.h"
#include "KingSystem/Resource/resResourceBoneControl.h"
#include "KingSystem/Resource/resResourceChemical.h"
#include "KingSystem/Resource/resResourceDamageParam.h"
#include "KingSystem/Resource/resResourceDrop.h"
#include "KingSystem/Resource/resResourceGParamList.h"
#include "KingSystem/Resource/resResourceLifeCondition.h"
#include "KingSystem/Resource/resResourceLod.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resResourceModelList.h"
#include "KingSystem/Resource/resResourcePhysics.h"
#include "KingSystem/Resource/resResourceRagdollBlendWeight.h"
#include "KingSystem/Resource/resResourceRagdollConfig.h"
#include "KingSystem/Resource/resResourceRagdollConfigList.h"
#include "KingSystem/Resource/resResourceRecipe.h"
#include "KingSystem/Resource/resResourceShop.h"
#include "KingSystem/Resource/resResourceUMii.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorParamMgr)

ActorParamMgr::ActorParamMgr() = default;

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

ActorParam* ActorParamMgr::loadParam(const char* actor_name, res::Handle* handle, void* x,
                                     u32 load_req_c) {
    bool allocated_new = false;
    ActorParam* param = allocParam(actor_name, &allocated_new);

    if (allocated_new) {
        loadFiles(param, mTmpActorParamMgrHeap, handle, x, load_req_c);
        param->setEventSignal();
    } else {
        param->waitForEvent();
    }

    return param;
}

void ActorParamMgr::loadFiles(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle,
                              void* x, u32 load_req_c) {
    param->deleteResHandles();
    param->allocResHandles(heap, 0, 29);
    param->mActiveBufferIdx = 0;

    using Type = ActorParam::ResourceType;
    using User = res::ActorLink::User;

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

void ActorParamMgr::loadFilesStep2(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle,
                                   void* x, u32 load_req_c) {
    const auto* link = param->getRes().mActorLink;
    param->mActiveBufferIdx = 0;

    using Type = ActorParam::ResourceType;
    using User = res::ActorLink::User;

    loadFile<res::AttClientList>(param, Type::AttClientList, "Actor/AttClientList", "atcllist",
                                 link->getUserName(User::Attention), pack_handle, x, load_req_c);

    loadFile<res::RagdollConfigList>(param, Type::RagdollConfigList, "Actor/RagdollConfigList",
                                     "rgconfiglist", link->getUserName(User::RgConfigList),
                                     pack_handle, x, load_req_c);

    {
        s32 num_extra_handles = 0;
        auto* aslist = param->getRes().mASList;
        auto* atcllist = param->getRes().mAttClientList;
        auto* rgconfiglist = param->getRes().mRagdollConfigList;
        if (aslist)
            num_extra_handles += aslist->getBuffers().as_defines.size();
        if (atcllist)
            num_extra_handles += atcllist->getClients().size();
        if (rgconfiglist)
            num_extra_handles += rgconfiglist->getImpulseParams().size();

        param->allocResHandles(heap, 1, num_extra_handles);
    }

    // Start loading the extra ActorParam files.
    param->mActiveBufferIdx = 1;

    if (auto* aslist = param->getRes().mASList) {
        for (s32 i = 0; i < aslist->getBuffers().as_defines.size(); ++i) {
            auto* as = loadFile<res::AS>(param, Type::AS, "Actor/AS", "as",
                                         aslist->getBuffers().as_defines[i].file_name.ref().cstr(),
                                         pack_handle, x, load_req_c);
            if (as) {
                as->setIndex(u32(Type::AS));
                aslist->addAS_(i, as);
            }
        }
    }

    if (auto* list = param->getRes().mAttClientList) {
        for (s32 i = 0; i < list->getClients().size(); ++i) {
            auto* client = loadFile<res::AttClient>(
                param, Type::AttClient, "Actor/AttClient", "atcl",
                list->getClients()[i].file_name.ref().cstr(), pack_handle, x, load_req_c);
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
                list->getImpulseParams()[i].file_name.ref().cstr(), pack_handle, x, load_req_c);
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
        res = sead::DynamicCast<T>(mResHandles[s32(type)].getResource());
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
    res = sead::DynamicCast<T>(mResHandles[s32(type)].getResource());
    sead::FixedSafeString<128> dummy_path;
    dummy_path.format("%s/Dummy.b%s", dir_name_c, extension_c);
    if (res) {
        static_cast<ParamIO*>(res)->getPath().copy(dummy_path);
        param->setResourceIfValidType(type, res);
    }

    return res;
}

res::GParamList* ActorParamMgr::getDummyGParamList() const {
    return static_cast<res::GParamList*>(
        mResHandles[u32(ActorParam::ResourceType::GParamList)].getResourceUnchecked());
}

}  // namespace ksys::act
