#include "KingSystem/Resource/resResourceASSetting.h"

namespace ksys::res {

ASSetting::ASSetting() {
    mType = "assetting";
    mVersion = 0;
}

ASSetting::~ASSetting() {
    mBlenderBones.freeBuffer();
}

void ASSetting::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool allocBlenderBones(sead::Buffer<ASSetting::BlenderBone>& buffer, int size, sead::Heap* heap,
                       int align = sizeof(void*)) {
    return buffer.tryAllocBuffer(size, heap, align);
}

bool ASSetting::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return true;

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    addList(&mBlenderBoneList, "BlenderBone");

    const auto lists = agl::utl::getResParameterList(root, "BlenderBone");
    if (!lists.ptr())
        return true;

    const auto num_blender_bones = lists.getResParameterListNum();
    if (num_blender_bones == 0)
        return true;

    if (!allocBlenderBones(mBlenderBones, num_blender_bones, heap))
        return false;

    auto res_it = lists.listBegin();
    const auto res_it_end = lists.listEnd();
    sead::FixedSafeString<32> list_name{"BlenderBone"};
    const auto list_name_base_len = list_name.calcLength();

    ASParamParser::ParseArgs args;
    args.res_list = {};
    args.heap = heap;

    auto it = mBlenderBones.begin();
    const auto end = mBlenderBones.end();
    for (; it != end && res_it != res_it_end; ++it, ++res_it) {
        list_name.trim(list_name_base_len);
        list_name.appendWithFormat("%d", it.getIndex());
        mBlenderBoneList.addList(&it->mList, list_name);

        it->mKeyName.init("", "KeyName", "キー名", "", &it->mNameParamObj);
        it->mList.addObj(&it->mNameParamObj, "NameParam");
        it->mList.addList(&it->mBoneParams.getList(), "BoneParam");

        const auto list = *res_it;
        args.list = &it->mList;
        args.res_list = agl::utl::getResParameterList(list, "BoneParam");
        if (!it->mBoneParams.parse(args))
            return false;
    }

    applyResParameterArchive(archive);
    return true;
}

ASSetting::BoneParams::~BoneParams() {
    mBuffer.freeBuffer();
}

bool ASSetting::BoneParams::parse(const ASParamParser::ParseArgs& args) {
    const auto num_objects = args.res_list.getResParameterObjNum();
    if (num_objects == 0)
        return true;

    if (!mBuffer.tryAllocBuffer(num_objects, args.heap))
        return false;

    auto it = mBuffer.begin();
    const auto end = mBuffer.end();

    sead::FixedSafeString<32> obj_name{"BoneParam"};
    const auto obj_name_base_len = obj_name.calcLength();

    auto res_it = args.res_list.objBegin();
    const auto res_end = args.res_list.objEnd();

    for (; it != end && res_it != res_end; ++it, ++res_it) {
        it->mBone.init("", "Bone", "ボーン名", "", &it->mObj);
        it->mWeight.init(0.0, "Weight", "ウェイト値", "Min=0.f,Max=1.f", &it->mObj);

        obj_name.trim(obj_name_base_len);
        obj_name.appendWithFormat("%d", res_it.getIndex());
        mList.addObj(&it->mObj, obj_name);
    }

    return true;
}

f32 ASSetting::BoneParams::getBoneWeight(const sead::SafeString& name) const {
    for (const auto& param : mBuffer) {
        if (name == *param.mBone)
            return *param.mWeight;
    }
    return 1.0;
}

}  // namespace ksys::res
