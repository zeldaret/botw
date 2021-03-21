#include "KingSystem/Chemical/chmRigid.h"

namespace ksys::chm {

Rigid::Rigid()
    : attribute(0, "attribute", "フラグ", this),
      rigid_set_name({""}, "rigid_set_name", "剛体セット名", this),
      rigid_name({""}, "rigid_name", "剛体名", this), volume(1.0, "volume", "直指定体積", this),
      mass(1.0, "mass", "直指定質量", this),
      burn_out_time(0.0, "burn_out_time", "燃え尽き時間", this) {}

}  // namespace ksys::chm
