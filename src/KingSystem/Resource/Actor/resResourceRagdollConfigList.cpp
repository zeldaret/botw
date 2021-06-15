#include "KingSystem/Resource/Actor/resResourceRagdollConfigList.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfig.h"

namespace ksys::res {

RagdollConfigList::RagdollConfigList()
    : ParamIO("rgconfiglist", 0),
      mUpperLimitHeight(0.0, "UpperLimitHight" /*sic*/, "ヒット位置判定の境界（上）", &mCommonData),
      mLowerLimitHeight(0.0, "LowerLimitHight" /*sic*/, "ヒット位置判定の境界（下）",
                        &mCommonData) {}

RagdollConfigList::~RagdollConfigList() {
    mImpulseParams.freeBuffer();
    mBodyParams.freeBuffer();
}

void RagdollConfigList::doCreate_(u8*, u32, sead::Heap*) {}

bool RagdollConfigList::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return false;

    if (RagdollConfig::cNumImpulseParams > 0) {
        mImpulseParams.allocBufferAssert(RagdollConfig::cNumImpulseParams, heap);
        if (!mImpulseParams.isBufferReady())
            return false;

#ifdef MATCHING_HACK_NX_CLANG
        __builtin_assume(RagdollConfig::cNumImpulseParams != 0);
#endif

        for (int i = 0; i != RagdollConfig::cNumImpulseParams; ++i) {
            mImpulseParams[i].config = nullptr;
            mImpulseParams[i].file_name.init("", "FileName", "データファイル名", "",
                                             &mImpulseParams[i].obj);
            mImpulseParamList.addObj(
                &mImpulseParams[i].obj,
                sead::FormatFixedSafeString<32>("%s%s", "ImpulseParam_",
                                                RagdollConfig::cImpulseParamNames[i].data()));
        }
    }
    addList(&mImpulseParamList, "ImpulseParamList");

    addObj(&mCommonData, "CommonData");

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();
    const auto BodyParamList = agl::utl::getResParameterList(root, "BodyParamList");
    if (int num_params;
        BodyParamList && (num_params = BodyParamList.getResParameterObjNum()) != 0) {
        mBodyParams.allocBufferAssert(num_params, heap);
        for (int i = 0; i < num_params; ++i) {
            mBodyParams[i].rigid_name.init(sead::SafeString::cEmptyString, "RigidName", "RigidName",
                                           "RigidName", &mBodyParams[i]);
            mBodyParams[i].friction_scale.init(1.0, "FrictionScale", "FrictionScale",
                                               "FrictionScale", &mBodyParams[i]);
            mBodyParams[i].buoyancy_scale.init(1.0, "BuoyancyScale", "BuoyancyScale",
                                               "BuoyancyScale", &mBodyParams[i]);
            mBodyParamList.addObj(&mBodyParams[i],
                                  sead::FormatFixedSafeString<32>("BodyParam_%d", i));
        }
    }
    addList(&mBodyParamList, "BodyParamList");

    applyResParameterArchive(archive);
    return true;
}

bool RagdollConfigList::finishParsing_() {
    return true;
}

bool RagdollConfigList::m7_() {
    for (auto& param : mImpulseParams)
        param.config = nullptr;

    return true;
}

}  // namespace ksys::res
