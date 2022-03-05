#pragma once

#include <container/seadObjArray.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct ContactPoint;
class RigidBody;

class LayerContactPointInfo : public ContactPointInfoBase {
public:
    struct LayerEntry {
        ContactLayer layer1;
        ContactLayer layer2;
        bool enabled;
    };

    class IteratorEnd;

    class Iterator {
    public:
        enum class Mode {
            _0,
            _1,
            _2,
        };

        Iterator(const Points& points, int count);

        Iterator& operator++() {
            ++mIdx;
            return *this;
        }

        // FIXME: rename
        void getData(sead::Vector3f* out, Mode mode) const;
        sead::Vector3f getData(Mode mode) const;

        const ContactPoint* getPoint() const { return mPoints[mIdx]; }
        const ContactPoint* operator*() const { return getPoint(); }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.mIdx == rhs.mIdx;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !operator==(lhs, rhs);
        }

    private:
        friend class IteratorEnd;

        int mIdx = 0;
        const ContactPoint* const* mPoints = nullptr;
        int mPointsNum = 0;
        const ContactPoint* const* mPointsStart = nullptr;
    };

    class IteratorEnd {
    public:
        IteratorEnd(const Points& points, int count);

        friend bool operator==(const Iterator& lhs, const IteratorEnd& rhs) {
            return lhs.mIdx == rhs.mIdx;
        }
        friend bool operator==(const IteratorEnd& lhs, const Iterator& rhs) {
            return lhs.mIdx == rhs.mIdx;
        }
        friend bool operator!=(const Iterator& lhs, const IteratorEnd& rhs) {
            return !operator==(lhs, rhs);
        }
        friend bool operator!=(const IteratorEnd& lhs, const Iterator& rhs) {
            return !operator==(lhs, rhs);
        }

    private:
        int mIdx = 0;
        const ContactPoint* const* mPoints = nullptr;
        int mPointsNum = 0;
        const ContactPoint* const* mPointsStart = nullptr;
    };

    struct ContactEvent {
        RigidBody* body_a;
        RigidBody* body_b;
        const sead::Vector3f* point_position;
        ContactLayer layer_a;
        ContactLayer layer_b;
        MaterialMaskData material_a;
        MaterialMaskData material_b;
    };

    using ContactCallback = sead::IDelegate1R<const ContactEvent&, bool>;

    static LayerContactPointInfo* make(sead::Heap* heap, int num, int num2,
                                       const sead::SafeString& name, int a, int b, int c);
    static void free(LayerContactPointInfo* instance);

    LayerContactPointInfo(const sead::SafeString& name, int a, int b, int c);
    ~LayerContactPointInfo() override;
    void freePoints() override;
    virtual void allocPoints(sead::Heap* heap, int num, int num2);

    bool registerLayerPair(ContactLayer layer1, ContactLayer layer2, bool enabled = true);
    bool isPairUnknown(ContactLayer layer1, ContactLayer layer2) const;

    ContactCallback* getCallback() const { return mCallback; }
    void setCallback(ContactCallback* callback) { mCallback = callback; }

    auto begin() const { return Iterator(mPoints, mContactPointIndex); }
    auto end() const { return IteratorEnd(mPoints, mContactPointIndex); }

    sead::ObjArray<LayerEntry>& getLayerEntries() { return mLayerEntries; }
    const sead::ObjArray<LayerEntry>& getLayerEntries() const { return mLayerEntries; }

private:
    friend class ContactMgr;

    Points mPoints;
    sead::ObjArray<LayerEntry> mLayerEntries;
    ContactLayerType mLayerType = ContactLayerType::Invalid;
    ContactCallback* mCallback = nullptr;
};
KSYS_CHECK_SIZE_NX150(LayerContactPointInfo, 0x88);

}  // namespace ksys::phys
