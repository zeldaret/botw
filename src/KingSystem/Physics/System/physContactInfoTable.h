#pragma once

#include <agl/Utils/aglResParameter.h>
#include "KingSystem/Physics/System/physDefines.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

// FIXME
class ContactInfoTable {
public:
    ContactInfoTable();
    virtual ~ContactInfoTable();

    void init(sead::Heap* heap);

    void load(sead::Heap* heap, agl::utl::ResParameterArchive archive, ContactLayerType type);
};

}  // namespace ksys::phys
