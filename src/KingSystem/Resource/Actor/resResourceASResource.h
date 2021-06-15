#pragma once

#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglResParameter.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::res {

class AS;

class ASResource {
    SEAD_RTTI_BASE(ASResource)
public:
    struct ParseArgs {
        agl::utl::ResParameterList list;
        sead::Heap* heap;
        AS* as;
        int index;
    };

    ASResource(int type_index, int index) : mTypeIndex(type_index), mIndex(index) {}
    virtual ~ASResource() = default;

    bool parse(const ParseArgs& args);

    virtual int m4() { return 0; }
    virtual int m5() { return 0; }
    virtual int m6() { return 1; }
    virtual int m7() { return 0; }

    static const sead::SafeString& getDefaultStr();
    static ASResource* make(const ParseArgs& args);

    u16 getTypeIndex() const { return mTypeIndex; }
    u16 getIndex() const { return mIndex; }
    int findStringIndex(const sead::SafeString& value) const;
    int findIntIndex(int value) const;

    agl::utl::ParameterList& getList() { return mList; }

protected:
    virtual bool doParse(const ParseArgs& args) { return true; }

    u16 mTypeIndex{};
    u16 mIndex{};
    agl::utl::ParameterList mList;
    ASExtensions mExtensions;
};

class ASResourceWithChildren : public ASResource {
    SEAD_RTTI_OVERRIDE(ASResourceWithChildren, ASResource)
public:
    using ASResource::ASResource;
    ~ASResourceWithChildren() override;
    ASResourceWithChildren(const ASResourceWithChildren&) = delete;
    auto operator=(const ASResourceWithChildren&) = delete;

    int m4() override { return callOnChildren_(&ASResource::m4); }
    int m5() override { return callOnChildren_(&ASResource::m5); }
    int m6() override { return callOnChildren_(&ASResource::m6) + 1; }

protected:
    using MemberFunction = int (ASResource::*)();

    bool doParse(const ParseArgs& args) override;
    virtual int callOnChildren_(MemberFunction fn);

    sead::Buffer<ASResource*> mChildren;
};

class ASSequencePlayContainerResource : public ASResourceWithChildren {
    SEAD_RTTI_OVERRIDE(ASSequencePlayContainerResource, ASResourceWithChildren)
public:
    using ASResourceWithChildren::ASResourceWithChildren;

    const auto& getSequenceLoop() const { return *mSequenceLoop; }
    float getValue(int index) const;

protected:
    bool doParse(const ParseArgs& args) override;
    int callOnChildren_(MemberFunction fn) override;
    int m7() override;

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<bool> mSequenceLoop;
};

class ASSelectorResource : public ASResourceWithChildren {
    SEAD_RTTI_OVERRIDE(ASSelectorResource, ASResourceWithChildren)
public:
    using ASResourceWithChildren::ASResourceWithChildren;

    const auto& getNoSync() const { return *mNoSync; }
    const auto& getJudgeOnce() const { return *mJudgeOnce; }

protected:
    bool doParse(const ParseArgs& args) override;
    int callOnChildren_(MemberFunction fn) override;

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<bool> mNoSync;
    agl::utl::Parameter<bool> mJudgeOnce;
};

class ASBlenderResource : public ASResourceWithChildren {
    SEAD_RTTI_OVERRIDE(ASBlenderResource, ASResourceWithChildren)
public:
    using ASResourceWithChildren::ASResourceWithChildren;

    const auto& getNoSync() const { return *mNoSync; }
    const auto& getJudgeOnce() const { return *mJudgeOnce; }
    const auto& getInputLimit() const { return *mInputLimit; }

protected:
    bool doParse(const ParseArgs& args) override;
    int callOnChildren_(MemberFunction fn) override;

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<bool> mNoSync;
    agl::utl::Parameter<bool> mJudgeOnce;
    agl::utl::Parameter<float> mInputLimit;
};

class ASAssetResource : public ASResource {
    SEAD_RTTI_OVERRIDE(ASAssetResource, ASResource)
public:
    using ASResource::ASResource;

    const sead::SafeString& getFileName() const { return *mFileName; }

protected:
    bool doParse(const ParseArgs& args) override;

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<sead::SafeString> mFileName;
};

class ASAssetExResource : public ASAssetResource {
    SEAD_RTTI_OVERRIDE(ASAssetExResource, ASAssetResource)
public:
    using ASAssetResource::ASAssetResource;

protected:
    int m5() override { return 1; }
};

class ASSkeltalAssetResource : public ASAssetResource {
    SEAD_RTTI_OVERRIDE(ASSkeltalAssetResource, ASAssetResource)
public:
    using ASAssetResource::ASAssetResource;

    const auto& getInitAnmDriven() const { return *mInitAnmDriven; }
    const auto& getMorph() const { return *mMorph; }
    const auto& getResetMorph() const { return *mResetMorph; }

protected:
    bool doParse(const ParseArgs& args) override;

    agl::utl::Parameter<int> mInitAnmDriven;
    agl::utl::Parameter<float> mMorph;
    agl::utl::Parameter<float> mResetMorph;
};

}  // namespace ksys::res
