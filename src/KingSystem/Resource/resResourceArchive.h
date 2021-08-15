#pragma once

#include <resource/seadSharcArchiveRes.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

struct ArchiveOffset {
    u32 mDataOffset = 0;
};

class Archive : public sead::SharcArchiveRes, public IResource, public ArchiveOffset {
    SEAD_RTTI_OVERRIDE(Archive, sead::SharcArchiveRes)
public:
    Archive();
    ~Archive() override;

    void doCreate_(u8* data, u32 size, sead::Heap* heap) override;

    static constexpr size_t cLoadDataAlignment = 0x80;
};
KSYS_CHECK_SIZE_NX150(Archive, 0x68);

}  // namespace ksys::res
