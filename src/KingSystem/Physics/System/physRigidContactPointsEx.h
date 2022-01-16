#pragma once

#include <container/seadObjArray.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physRigidContactPoints.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct ContactPoint;

// FIXME: rename. This should be below SensorGroupFilter and StaticCompound stuff
class RigidContactPointsEx : public IRigidContactPoints {
public:
    using Points = sead::Buffer<ContactPoint*>;

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

    // FIXME: figure out the types
    using Callback = sead::IDelegate1<void*>;

    static RigidContactPointsEx* make(sead::Heap* heap, int num, int num2,
                                      const sead::SafeString& name, int a, int b, int c);
    static void free(RigidContactPointsEx* instance);

    RigidContactPointsEx(const sead::SafeString& name, int a, int b, int c);
    ~RigidContactPointsEx() override;
    void freePoints() override;
    virtual void allocPoints(sead::Heap* heap, int num, int num2);

    bool registerLayerPair(ContactLayer layer1, ContactLayer layer2, bool enabled = true);
    bool isPairUnknown(ContactLayer layer1, ContactLayer layer2) const;

    void setCallback(Callback* callback) { mCallback = callback; }

    auto begin() const { return Iterator(mPoints, _18); }
    auto end() const { return IteratorEnd(mPoints, _18); }

private:
    struct LayerEntry {
        ContactLayer layer1;
        ContactLayer layer2;
        bool enabled;
    };

    Points mPoints{};
    sead::ObjArray<LayerEntry> mLayerEntries;
    ContactLayerType mLayerType = ContactLayerType::Invalid;
    Callback* mCallback = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidContactPointsEx, 0x88);

}  // namespace ksys::phys
