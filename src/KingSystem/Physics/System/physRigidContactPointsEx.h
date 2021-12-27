#pragma once

#include <container/seadObjArray.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physRigidContactPoints.h"

namespace ksys::phys {

// FIXME: rename. This should be below SensorGroupFilter and StaticCompound stuff
class RigidContactPointsEx : public IRigidContactPoints {
public:
    static RigidContactPointsEx* make();
    static void free(RigidContactPointsEx* instance);

    RigidContactPointsEx(const sead::SafeString& name, int a, int b, int c);
    ~RigidContactPointsEx() override;
    virtual void freePoints();
    virtual void allocPoints(sead::Heap* heap, int num, int num2);

    bool registerLayerPair(ContactLayer layer1, ContactLayer layer2, bool enabled);
    bool isPairUnknown(ContactLayer layer1, ContactLayer layer2) const;

private:
    struct LayerEntry {
        ContactLayer layer1;
        ContactLayer layer2;
        bool enabled;
    };

    sead::Buffer<void*> mPoints{};
    sead::ObjArray<LayerEntry> mLayerEntries;
    ContactLayerType mLayerType = ContactLayerType::Invalid;
    void* _80 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidContactPointsEx, 0x88);

}  // namespace ksys::phys
