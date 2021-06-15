#include "KingSystem/Physics/SupportBone/physSupportBoneParam.h"

namespace ksys::phys {

SupportBoneParam::SupportBoneParam()
    : support_bone_setup_file_path(sead::SafeString::cEmptyString, "support_bone_setup_file_path",
                                   "補助骨セットアップファイル(.psb)", this) {}

}  // namespace ksys::phys
