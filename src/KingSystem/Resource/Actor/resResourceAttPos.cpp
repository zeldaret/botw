#include "KingSystem/Resource/Actor/resResourceAttPos.h"

namespace ksys::res {

AttPos::AttPos() = default;

void AttPos::init(agl::utl::IParameterObj* obj, const char* node_key, const char* offset_key,
                  const char* rotate_key, const char* y_rot_only_key) {
    node.init("", node_key, "ノード", "", obj);
    offset.init(sead::Vector3f::zero, offset_key, "オフセット", "Min=-100.f,Max=100.f", obj);
    rotate.init(sead::Vector3f::zero, rotate_key, "回転", "Min=-3.1415f,Max=3.1415f", obj);
    y_rot_only.init(false, y_rot_only_key, "Ｙ軸回転のみ有効", "", obj);
}

}  // namespace ksys::res
