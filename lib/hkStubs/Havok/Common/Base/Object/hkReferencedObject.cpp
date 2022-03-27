#include <Havok/Common/Base/hkBase.h>

const hkClass* hkReferencedObject::getClassType() const {
    return nullptr;
}

void hkReferencedObject::deleteThisReferencedObject() const {
    delete this;
}
