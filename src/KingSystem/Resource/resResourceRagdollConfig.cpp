#include "KingSystem/Resource/resResourceRagdollConfig.h"

namespace ksys::res {

RagdollConfig::RagdollConfig() : ParamIO("rgconfig", 0) {}

RagdollConfig::~RagdollConfig() = default;

void RagdollConfig::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool RagdollConfig::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return false;

    addList(&mConfig, "ConfigRoot");

    agl::utl::ResParameterArchive archive{data};
    applyResParameterArchive(archive);
    return true;
}

}  // namespace ksys::res
