#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include <codec/seadHashCRC32.h>
#include <heap/seadHeapMgr.h>

namespace ksys::res {

ActorLink::ActorLink() : ParamIO("xml", 0) {
    const auto init_user = [this](auto& param, const char* key, const char* default_ = "Dummy") {
        param.init(default_, key, "", &mUsers.obj);
    };
    init_user(mUsers.profile, "ProfileUser");
    init_user(mUsers.actor_capture, "ActorCaptureUser");
    init_user(mUsers.as, "ASUser", "");
    init_user(mUsers.model, "ModelUser", "");
    init_user(mUsers.anim, "AnimUser", "");
    init_user(mUsers.ai_program, "AIProgramUser", "");
    init_user(mUsers.gparam, "GParamUser", "");
    init_user(mUsers.damage_param, "DamageParamUser");
    init_user(mUsers.rg_config_list, "RgConfigListUser");
    init_user(mUsers.rg_blend_weight, "RgBlendWeightUser");
    init_user(mUsers.awareness, "AwarenessUser");
    init_user(mUsers.elink, "ElinkUser");
    init_user(mUsers.slink, "SlinkUser");
    init_user(mUsers.xlink, "XlinkUser");
    init_user(mUsers.attention, "AttentionUser");
    init_user(mUsers.physics, "PhysicsUser");
    init_user(mUsers.chemical, "ChemicalUser");
    init_user(mUsers.drop_table, "DropTableUser");
    init_user(mUsers.shop_data, "ShopDataUser");
    init_user(mUsers.recipe, "RecipeUser");
    init_user(mUsers.lod, "LODUser");
    init_user(mUsers.ai_schedule, "AIScheduleUser");
    init_user(mUsers.bone_control, "BoneControlUser");
    init_user(mUsers.life_condition, "LifeConditionUser");
    init_user(mUsers.umii, "UMiiUser");
    init_user(mUsers.animation_info, "AnimationInfo");

    mActorScale.init(1.0, "ActorScale", "", &mUsers.obj);
    mActorNameJpn.init("不正な名前", "ActorNameJpn", "ActorNameJpn", &mUsers.obj);
    mPriority.init("", "Priority", "Priority", &mUsers.obj);

    addObj(&mUsers.obj, "LinkTarget");
}

bool ActorLink::parse_(u8* data, size_t, sead::Heap* heap) {
    if (!data)
        return true;

    const agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    const s32 tags_idx = root.searchObjIndex(agl::utl::ParameterBase::calcHash("Tags"));
    // NON_MATCHING: getResParameter (redundant uxtw; i and res increment order)
    const auto parse_tags = [&] {
        if (tags_idx == -1)
            return;

        const auto obj = root.getResParameterObj(tags_idx);
        if (!obj.ptr())
            return;

        const auto num_tags = obj.getNum();
        if (num_tags == 0)
            return;

        mHeap = heap;
        mTags.allocBufferAssert(num_tags, heap);

        for (s32 i = 0; i != num_tags; ++i) {
            const char* tag = obj.getResParameter(i).getData<char>();
            mTags[i] = sead::HashCRC32::calcStringHash(tag);
        }

        if (num_tags > 1)
            mTags.heapSort(0, num_tags - 1);
    };
    parse_tags();

    applyResParameterArchive(agl::utl::ResParameterArchive{data});
    return true;
}

void ActorLink::finalize_() {
    if (!mTags.isBufferReady())
        return;

    if (!mHeap)
        return;

    sead::ScopedCurrentHeapSetter setter{mHeap};
    mTags.freeBuffer();
}

// NON_MATCHING: operands are swapped for an equality comparison in binarySearch
bool ActorLink::hasTag(const char* tag_name) const {
    return mTags.size() >= 1 && mTags.binarySearch(sead::HashCRC32::calcStringHash(tag_name)) != -1;
}

bool ActorLink::hasTag(u32 tag) const {
    return mTags.size() >= 1 && mTags.binarySearch(tag) != -1;
}

}  // namespace ksys::res
