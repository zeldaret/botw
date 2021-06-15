#include "KingSystem/Resource/Actor/resResourceAnimInfo.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::res {

AnimInfo::AnimInfo() : ParamIO("animinfo", 0) {}

AnimInfo::~AnimInfo() {
    mAnims.freeBuffer();

    if (mSwordBlurInfo) {
        mSwordBlurInfo->finalize();
        util::safeDelete(mSwordBlurInfo);
    }
}

void AnimInfo::SwordBlurInfo::finalize() {
    if (!entries)
        return;

    for (int i = 0; i < num_entries; ++i) {
        SwordBlur& entry = entries[i];
        auto* h = heap;
        if (entry.frames) {
            h->free(entry.frames);
            entry.frames = nullptr;
        }
        if (entry._18) {
            h->free(entry._18);
            entry._18 = nullptr;
        }
    }

    heap->free(entries);
    entries = nullptr;
}

void AnimInfo::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool AnimInfo::parse_(u8* data, size_t size, sead::Heap* heap) {
    al::ByamlIter root_iter{data};

    const int num_entries = root_iter.getSize();
    int num_anims = num_entries - 1;
    if (num_entries < 1)
        return true;

    al::ByamlIter iter;
    int double_attack_anm_num = 0;
    int num = 0;
    bool allocate_anims = false;
    if (root_iter.isExistKey("_sword_blur")) {
        iter = root_iter.getIterByKey("_sword_blur");
        const int num_sword_blurs = iter.getSize();
        iter.tryGetIntByKey(&double_attack_anm_num, "double_attack_anm_num");
        num = num_sword_blurs - 1;
        if (num_entries > 1)
            allocate_anims = true;
    } else {
        num = 0;
        num_anims = num_entries;
        allocate_anims = true;
    }

    if (allocate_anims) {
        if (!mAnims.tryAllocBuffer(num_anims, heap))
            return false;

        for (int i = 0; i < num_anims; ++i) {
            auto& anim = mAnims[i];
            anim.scale.e.fill(0.0);

            al::ByamlIter entry_iter;
            if (root_iter.tryGetIterByIndex(&entry_iter, i)) {
                const char* name_c;
                if (root_iter.getKeyName(&name_c, i)) {
                    if (std::strcmp(name_c, "_sword_blur") == 0)
                        continue;
                    anim.name = name_c;
                } else {
                    anim.name = "";
                }
                entry_iter.tryGetFloatByKey(&anim.scale.x, "scaleX");
                entry_iter.tryGetFloatByKey(&anim.scale.y, "scaleY");
                entry_iter.tryGetFloatByKey(&anim.scale.z, "scaleZ");
            } else {
                anim.name = "";
            }
        }
    }

    if (num >= 1) {
        if (!mSwordBlurInfo) {
            auto* info = new (heap) SwordBlurInfo;
            info->entries = nullptr;
            mSwordBlurInfo = info;
            info->heap = heap;
            info->num_entries = double_attack_anm_num;
            /// @bug SwordBlur is not trivially constructible and not trivially copyable.
            /// The only reason using SwordBlur::name doesn't crash is that Clang and GHS
            /// are smart enough to devirtualize sead::SafeString virtual function calls,
            /// which removes the need to go through the vtable.
#ifdef AVOID_UB
            info->entries = new (heap) SwordBlur[info->num_entries];
#else
            info->entries = static_cast<SwordBlur*>(
                heap->tryAlloc(sizeof(SwordBlur) * info->num_entries, alignof(SwordBlur)));
            std::memset(info->entries, 0, sizeof(SwordBlur) * info->num_entries);
#endif
        }

        // TODO / FIXME: finish this
    }

    return true;
}

const AnimInfo::Anim* AnimInfo::getAnim(const sead::SafeString& name) const {
    const auto idx = findAnimIndex(name);
    if (idx < 0)
        return nullptr;
    return &mAnims[idx];
}

int AnimInfo::findAnimIndex(const sead::SafeString& name) const {
    return mAnims.binarySearch(
        name,
        +[](const Anim& anim, const sead::SafeString& key) { return anim.name.compare(key); });
}

}  // namespace ksys::res
