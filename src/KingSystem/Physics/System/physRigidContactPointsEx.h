#pragma once

#include <container/seadObjArray.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physRigidContactPoints.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// FIXME: rename. This should be below SensorGroupFilter and StaticCompound stuff
class RigidContactPointsEx : public IRigidContactPoints {
public:
    struct Point {
        enum class Flag {
            _1 = 1 << 0,
            _2 = 1 << 1,
        };

        void* _0;
        void* _8;
        sead::Vector3f _10;
        sead::Vector3f _1c;
        float scale;
        void* _30;
        void* _38;
        void* _40;
        void* _48;
        void* _50;
        void* _58;
        void* _60;
        sead::TypedBitFlag<Flag, u8> flags;
    };
    KSYS_CHECK_SIZE_NX150(Point, 0x70);

    using Points = sead::Buffer<Point*>;

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

        const Point* getPoint() const { return mPoints[mIdx]; }
        const Point* operator*() const { return getPoint(); }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.mIdx == rhs.mIdx;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !operator==(lhs, rhs);
        }

    private:
        friend class IteratorEnd;

        int mIdx = 0;
        const Point* const* mPoints = nullptr;
        int mPointsNum = 0;
        const Point* const* mPointsStart = nullptr;
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
        const Point* const* mPoints = nullptr;
        int mPointsNum = 0;
        const Point* const* mPointsStart = nullptr;
    };

    static RigidContactPointsEx* make();
    static void free(RigidContactPointsEx* instance);

    RigidContactPointsEx(const sead::SafeString& name, int a, int b, int c);
    ~RigidContactPointsEx() override;
    virtual void freePoints();
    virtual void allocPoints(sead::Heap* heap, int num, int num2);

    bool registerLayerPair(ContactLayer layer1, ContactLayer layer2, bool enabled);
    bool isPairUnknown(ContactLayer layer1, ContactLayer layer2) const;

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
    void* _80 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidContactPointsEx, 0x88);

}  // namespace ksys::phys
