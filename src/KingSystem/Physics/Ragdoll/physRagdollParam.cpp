#include "KingSystem/Physics/Ragdoll/physRagdollParam.h"
#include <filedevice/seadPath.h>

namespace ksys::phys {

RagdollParam::RagdollParam()
    : contact_point_info(sead::SafeString::cEmptyString, "contact_point_info", this),
      collision_info(sead::SafeString::cEmptyString, "collision_info", this),
      ragdoll_setup_file_path(sead::SafeString::cEmptyString, "ragdoll_setup_file_path", this) {}

RagdollParam::~RagdollParam() = default;

void RagdollParam::postRead_() {
    sead::Path::getFileName(&ragdoll_setup_file_stem, ragdoll_setup_file_path.ref());
    ragdoll_setup_file_stem.removeSuffix(".hkrg");
}

}  // namespace ksys::phys
