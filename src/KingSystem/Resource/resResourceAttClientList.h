#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class AttClientList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClientList, Resource)
public:
    struct AttPos {
        agl::utl::Parameter<sead::SafeString> _0;
        agl::utl::Parameter<sead::Vector3f> _28;
        agl::utl::Parameter<sead::Vector3f> _50;
        agl::utl::Parameter<bool> _78;
    };
    KSYS_CHECK_SIZE_NX150(AttPos, 0x98);

    struct Client {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<sead::SafeString> file_name;
        agl::utl::Parameter<bool> is_valid;
        agl::utl::ParameterObj obj;
        void* _a0;
    };
    KSYS_CHECK_SIZE_NX150(Client, 0xa8);

    AttClientList() : ParamIO("atcllist", 0) {}

    const AttPos& getAttPos() const { return mAttPos; }
    bool isForceEdit() const { return mForceEdit.ref(); }
    const sead::Buffer<Client>& getClients() const { return mClients; }

private:
    agl::utl::ParameterList mAttClientsList;
    agl::utl::ParameterObj mAttPosObj;
    AttPos mAttPos;
    agl::utl::Parameter<bool> mForceEdit;
    sead::Buffer<Client> mClients;
};
KSYS_CHECK_SIZE_NX150(AttClientList, 0x3f0);

}  // namespace ksys::res
