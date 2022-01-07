#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"

namespace ksys::phys {

RagdollControllerKeyList::RagdollControllerKey::RagdollControllerKey()
    : key(sead::SafeString::cEmptyString, "key", this), hierarchy_gain(0, "hierarchy_gain", this),
      velocity_damping(0, "velocity_damping", this),
      acceleration_gain(0, "acceleration_gain", this), velocity_gain(0, "velocity_gain", this),
      position_gain(0, "position_gain", this),
      position_max_linear_velocity(0, "position_max_linear_velocity", this),
      position_max_angular_velocity(0, "position_max_angular_velocity", this),
      snap_gain(0, "snap_gain", this),
      snap_max_linear_velocity(0, "snap_max_linear_velocity", this),
      snap_max_angular_velocity(0, "snap_max_angular_velocity", this),
      snap_max_linear_distance(0, "snap_max_linear_distance", this),
      snap_max_angular_distance(0, "snap_max_angular_distance", this) {}

RagdollControllerKeyList::RagdollControllerKeyList() = default;
RagdollControllerKeyList::~RagdollControllerKeyList() {
    buffer.freeBuffer();
}

RagdollControllerKeyList::RagdollControllerKey*
RagdollControllerKeyList::getControllerKeyByKey(const sead::SafeString& key) {
    int buffer_size = buffer.size();
    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i].key.ref() == key) {
            return &buffer[i];
        }
    }
    return nullptr;
}

bool RagdollControllerKeyList::parse_(u8* data, size_t actualFileSize, sead::Heap* heap) {
    if (!data)
        return false;

    auto archive = agl::utl::ResParameterArchive(data);
    auto key_list = agl::utl::getResParameterList(archive.getRootList(), "RagCtrlKeyList");
    if (!key_list)
        return false;

    int key_count = key_list.getResParameterObjNum();
    if (key_count == 0)
        return false;

    buffer.allocBufferAssert(key_count, heap);

    for (int i = 0; i < key_count; i++) {
        buffer[i].applyResParameterObj(key_list.getResParameterObj(i));
    }

    return true;
}

}  // namespace ksys::phys
