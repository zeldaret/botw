#include <Havok/Common/Base/Object/hkReferencedObject.h>

const hkClass* hkReferencedObject::getClassType() const {
    return nullptr;
}

void hkReferencedObject::deleteThisReferencedObject() const {
    delete this;
}
