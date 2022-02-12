#pragma once

#include <Havok/Common/Base/Object/hkReferencedObject.h>

namespace ksys::phys {

template <typename T>
inline std::enable_if_t<std::is_base_of_v<hkReferencedObject, T>, void>
deleteRefCountedHavokObject(T*& object) {
    if (!object)
        return;

    /// @bug This should just be a delete expression. Decrementing the reference count
    /// n times (with n = the reference count) is not how reference counting is supposed to work.
    for (int i = 0, n = object->getReferenceCount(); i < n; ++i)
        object->removeReference();

    object = nullptr;
}

}  // namespace ksys::phys
