#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Attention/actAttention.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

struct AttPos {
    AttPos();

    void init(agl::utl::IParameterObj* obj, const char* node_key = "Node",
              const char* offset_key = "Offset", const char* rotate_key = "Rotate",
              const char* y_rot_only_key = "YRotOnly");

    // TODO: more functions

    agl::utl::Parameter<sead::SafeString> node;
    agl::utl::Parameter<sead::Vector3f> offset;
    agl::utl::Parameter<sead::Vector3f> rotate;
    agl::utl::Parameter<bool> y_rot_only;
};
KSYS_CHECK_SIZE_NX150(AttPos, 0x98);

class AttClient : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClient, Resource)
public:
    struct Check {};

    AttClient() : ParamIO("atcl", 0) {}
    ~AttClient() override;

    act::AttType getAttType() const { return mAttType; }
    act::AttActionCode getActionCode() const { return mActionCode; }
    act::AttPriorityType getPriorityType() const { return mPriorityType; }
    const sead::SafeString& getPriorityTypeStr() const { return mPriorityTypeStr; }
    const sead::Buffer<Check*>& getChecks() const { return mChecks; }

    void doCreate_(u8*, u32, sead::Heap*) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

private:
    act::AttType mAttType = act::AttType::Action;
    act::AttActionCode mActionCode = act::AttActionCode::None;
    act::AttPriorityType mPriorityType = act::AttPriorityType::Default;
    sead::FixedSafeString<32> mPriorityTypeStr;
    agl::utl::ParameterObj mAttClientParamsObj;
    agl::utl::Parameter<sead::FixedSafeString<32>> mAttTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mActionTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mPriorityTypeParam;
    sead::Buffer<Check*> mChecks;
};
KSYS_CHECK_SIZE_NX150(AttClient, 0x428);

class AttClientList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClientList, Resource)
public:
    struct Client {
        const char* getFileName() const { return file_name.ref().cstr(); }

        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<sead::SafeString> file_name;
        agl::utl::Parameter<bool> is_valid;
        agl::utl::ParameterObj obj;
        AttClient* client;
    };
    KSYS_CHECK_SIZE_NX150(Client, 0xa8);

    AttClientList() : ParamIO("atcllist", 0) {}
    ~AttClientList() override;
    AttClientList(const AttClientList&) = delete;
    auto operator=(const AttClientList&) = delete;

    const AttPos& getAttPos() const { return mAttPos; }
    bool isForceEdit() const { return mForceEdit.ref(); }
    const sead::Buffer<Client>& getClients() const { return mClients; }

    void addClient_(s32 index, AttClient* client) { mClients[index].client = client; }

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    bool finishParsing_() override;
    bool m7_() override;

private:
    agl::utl::ParameterList mAttClientsList;
    agl::utl::ParameterObj mAttPosObj;
    AttPos mAttPos;
    agl::utl::Parameter<bool> mForceEdit;
    sead::Buffer<Client> mClients;
};
KSYS_CHECK_SIZE_NX150(AttClientList, 0x3f0);

}  // namespace ksys::res
