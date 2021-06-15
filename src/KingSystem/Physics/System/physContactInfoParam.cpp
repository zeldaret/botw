#include "KingSystem/Physics/System/physContactInfoParam.h"

namespace ksys::phys {

ContactInfoParam::ContactInfoParam()
    : contact_point_info_num(0, "contact_point_info_num", &obj),
      collision_info_num(0, "collision_info_num", &obj) {}

ContactInfoParam::~ContactInfoParam() {
    contact_point_info.freeBuffer();
    collision_info.freeBuffer();
}

bool ContactInfoParam::parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap) {
    if (!res_list || res_list.getResParameterObjNum() < 1)
        return false;

    obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_contact_point_info = *contact_point_info_num;
    const int num_collision_info = *collision_info_num;

    if (num_contact_point_info > 0) {
        contact_point_info.allocBufferAssert(num_contact_point_info, heap);
        for (int i = 0; i < num_contact_point_info; ++i) {
            addObj(&contact_point_info[i],
                   sead::FormatFixedSafeString<32>("ContactPointInfo_%d", i));
        }
    }

    if (num_collision_info > 0) {
        collision_info.allocBufferAssert(num_collision_info, heap);
        for (int i = 0; i < num_collision_info; ++i) {
            addObj(&collision_info[i], sead::FormatFixedSafeString<32>("CollisionInfo_%d", i));
        }
    }

    applyResParameterList(res_list);
    return true;
}

ContactPointInfoParam::ContactPointInfoParam()
    : name(sead::SafeString::cEmptyString, "name", this),
      type(sead::SafeString::cEmptyString, "type", this), num(0x80, "num", this) {}

CollisionInfoParam::CollisionInfoParam()
    : name(sead::SafeString::cEmptyString, "name", this),
      type(sead::SafeString::cEmptyString, "type", this) {}

}  // namespace ksys::phys
