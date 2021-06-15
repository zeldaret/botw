#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

// TODO
class AnimInfo : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AnimInfo, Resource)
public:
    struct Anim {
        sead::SafeString name;
        sead::Vector3f scale;
    };
    KSYS_CHECK_SIZE_NX150(Anim, 0x20);

    struct SwordBlur {
        int frame_num;
        int start;
        int end;
        sead::Matrix34f* frames;
        float* _18;
        sead::SafeString name;
    };
    KSYS_CHECK_SIZE_NX150(SwordBlur, 0x30);

    AnimInfo();
    ~AnimInfo() override;

    bool needsParse() const override { return true; }
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const sead::Buffer<Anim>& getAnims() const { return mAnims; }

    const Anim* getAnim(const sead::SafeString& name) const;
    int findAnimIndex(const sead::SafeString& name) const;

private:
    struct SwordBlurInfo {
        void finalize();

        sead::Heap* heap;
        int num_entries;
        SwordBlur* entries;
    };
    KSYS_CHECK_SIZE_NX150(SwordBlurInfo, 0x18);

    sead::Buffer<Anim> mAnims;
    SwordBlurInfo* mSwordBlurInfo = nullptr;
};

}  // namespace ksys::res
