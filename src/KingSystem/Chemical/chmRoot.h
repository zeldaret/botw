#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Chemical/chmRigid.h"
#include "KingSystem/Chemical/chmShape.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::chm {

class IRoot {
public:
    virtual int getNumShapes() const = 0;
    virtual const IShape& getShape(int idx) const = 0;

    virtual bool isRigidAttribute0Set(int idx) const = 0;
    virtual bool isRigidAttribute1Set(int idx) const = 0;
    virtual const sead::SafeString& getRigidSetName(int idx) const = 0;
    virtual bool isRigidAttribute2Set(int idx) const = 0;
    virtual const sead::SafeString& getRigidName(int idx) const = 0;
    virtual bool rigidHasBurnOutTime(int idx) const = 0;
    virtual float getRigidBurnOutTime(int idx) const = 0;
    virtual bool isRigidAttribute3Set(int idx) const = 0;
    virtual bool isRigidAttribute15Set(int idx) const = 0;
    virtual float getRigidVolume(int idx) const = 0;
    virtual bool isRigidAttribute9Set(int idx) const = 0;
    virtual bool isRigidAttribute10Set(int idx) const = 0;
    virtual float getRigidMass(int idx) const = 0;
    virtual bool isRigidAttribute6Or14Set(int idx) const = 0;
    virtual bool isRigidAttribute5Set(int idx) const = 0;
    virtual bool isRigidAttribute4Set(int idx) const = 0;
    virtual bool isRigidAttribute11Set(int idx) const = 0;
    virtual bool isRigidAttribute12Set(int idx) const = 0;
    virtual bool isRigidAttribute13Set(int idx) const = 0;
    virtual bool isRigidAttribute14Set(int idx) const = 0;
    virtual bool isRigidAttribute16Set(int idx) const = 0;
};

class Root : public agl::utl::ParameterList, public sead::hostio::Node, public IRoot {
public:
    Root();
    ~Root() override;
    Root(const Root&) = delete;
    auto operator=(const Root&) = delete;

    void parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap);

    int getNumShapes() const override { return shapes.size(); }
    const IShape& getShape(int idx) const override { return shapes[idx]; }
    bool isRigidAttribute0Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 0);
    }
    bool isRigidAttribute1Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 1);
    }
    const sead::SafeString& getRigidSetName(int idx) const override {
        return rigids[idx].getRigidSetName();
    }
    bool isRigidAttribute2Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 2);
    }
    const sead::SafeString& getRigidName(int idx) const override {
        return rigids[idx].getRigidName();
    }
    bool rigidHasBurnOutTime(int idx) const override { return rigids[idx].getBurnOutTime() > 0.0; }
    float getRigidBurnOutTime(int idx) const override { return rigids[idx].getBurnOutTime(); }
    bool isRigidAttribute3Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 3);
    }
    bool isRigidAttribute15Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 15);
    }
    float getRigidVolume(int idx) const override { return rigids[idx].getVolume(); }
    bool isRigidAttribute9Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 9);
    }
    bool isRigidAttribute10Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 10);
    }
    float getRigidMass(int idx) const override { return rigids[idx].getMass(); }
    bool isRigidAttribute6Or14Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 6) || isRigidAttribute14Set(idx);
    }
    bool isRigidAttribute5Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 5);
    }
    bool isRigidAttribute4Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 4);
    }
    bool isRigidAttribute11Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 11);
    }
    bool isRigidAttribute12Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 12);
    }
    bool isRigidAttribute13Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 13);
    }
    bool isRigidAttribute14Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 14);
    }
    bool isRigidAttribute16Set(int idx) const override {
        return rigids[idx].getAttribute() & (1 << 16);
    }

private:
    agl::utl::ParameterObj chemical_header;
    agl::utl::Parameter<u32> res_shape_num;
    agl::utl::ParameterList chemical_body;
    sead::Buffer<Shape> shapes;
    sead::Buffer<Rigid> rigids;
};

}  // namespace ksys::chm
