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

namespace sead {
class Heap;
}

namespace ksys::phys {

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

class ContactMgr : public sead::hostio::Node {
public:
    ContactMgr();
    virtual ~ContactMgr();

    void init(sead::Heap* heap);

    void loadContactInfoTable(sead::Heap* heap, agl::utl::ResParameterArchive archive,
                              ContactLayerType type);

    bool getSensorLayerMask(ReceiverMask* mask, const sead::SafeString& receiver_type) const;

private:
    void doLoadContactInfoTable(agl::utl::ResParameterArchive archive, ContactLayerType type,
                                bool skip_params);

    // FIXME: type, name
    sead::Buffer<void*> mBuffer;
    sead::OffsetList<void*> mList0;
    int mList0Size = 0;
    sead::Atomic<int> _34 = 0;
    sead::OffsetList<void*> mList1;
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
