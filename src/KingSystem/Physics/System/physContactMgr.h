#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <agl/Utils/aglResParameter.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadMutex.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class IRigidContactPoints;
class RigidContactPoints;
class RigidContactPointsEx;

struct ContactInfoTable {
    struct Receiver : agl::utl::ParameterObj {
        const char* name = nullptr;
        // TODO: figure out what these masks are
        u32 layer_mask = 0;
        u32 layer_mask2 = 0;
        int num_layers = 0;
        sead::SafeArray<agl::utl::Parameter<int>, MaxNumLayersPerType> layer_values;

    protected:
        void postRead_() override;
    };

    agl::utl::IParameterIO param_io;
    agl::utl::ParameterList contact_info_table_plist;
    sead::Buffer<Receiver> receivers;
};

// XXX: what exactly is this? Is this really a contact point?
struct ContactPoint {
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
KSYS_CHECK_SIZE_NX150(ContactPoint, 0x70);

class ContactMgr : public sead::hostio::Node {
public:
    ContactMgr();
    virtual ~ContactMgr();

    void init(sead::Heap* heap);

    void loadContactInfoTable(sead::Heap* heap, agl::utl::ResParameterArchive archive,
                              ContactLayerType type);

    bool getSensorLayerMask(ReceiverMask* mask, const sead::SafeString& receiver_type) const;

    RigidContactPoints* allocContactPoints(sead::Heap* heap, int num, const sead::SafeString& name,
                                           int a, int b, int c);
    RigidContactPointsEx* allocContactPointsEx(sead::Heap* heap, int num, int num2,
                                               const sead::SafeString& name, int a, int b, int c);
    void registerContactPoints(IRigidContactPoints* points);
    void freeContactPoints(IRigidContactPoints* points);

private:
    void doLoadContactInfoTable(agl::utl::ResParameterArchive archive, ContactLayerType type,
                                bool skip_params);

    // FIXME: type, name
    sead::Buffer<void*> mBuffer;
    sead::OffsetList<void*> mList0;
    int mList0Size = 0;
    sead::Atomic<int> _34 = 0;
    sead::OffsetList<IRigidContactPoints> mRigidContactPoints;
    sead::OffsetList<void*> mList2;
    sead::OffsetList<void*> mList3;
    sead::OffsetList<void*> mList4;
    sead::OffsetList<void*> mList5;
    sead::Mutex mMutex1;
    sead::Mutex mMutex2;
    sead::Mutex mMutex3;
    sead::Mutex mMutex4;
    sead::Mutex mMutex5;
    sead::SafeArray<ContactInfoTable, 2> mContactInfoTables{};
};

}  // namespace ksys::phys
