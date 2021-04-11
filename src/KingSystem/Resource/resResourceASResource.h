#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <agl/Utils/aglResParameter.h>
#include <array>
#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::res {

class ASParamParser {
    SEAD_RTTI_BASE(ASParamParser)
public:
    enum class Type {
        FrameCtrl = 0,
        TriggerEvents = 1,
        HoldEvents = 2,
        StringArray = 3,
        Ranges = 4,
        FloatArray = 5,
        IntArray = 6,
        BitIndex = 7,
        BlenderBone = 8,
    };
    static constexpr int NumTypes = 9;

    struct ParseArgs {
        agl::utl::ParameterList* list;
        agl::utl::ResParameterList res_list;
        sead::Heap* heap;
    };

    explicit ASParamParser(Type type) : mType(type) {}
    virtual ~ASParamParser() = default;
    virtual bool parse(const ParseArgs& args) { return true; }

    Type getType() const { return mType; }
    agl::utl::ParameterList& getList() { return mList; }
    const agl::utl::ParameterList& getList() const { return mList; }

protected:
    Type mType;
    agl::utl::ParameterList mList;
};
KSYS_CHECK_SIZE_NX150(ASParamParser, 0x58);

class ASExtensions {
public:
    struct ParseArgs {
        agl::utl::ResParameterList res_list;
        agl::utl::ParameterList* list;
        sead::Heap* heap;
    };

    ASExtensions() = default;
    ~ASExtensions();
    ASExtensions(const ASExtensions&) = delete;
    auto operator=(const ASExtensions&) = delete;

    const sead::Buffer<ASParamParser*>& getParsers() const { return mParsers; }
    ASParamParser* getParser(ASParamParser::Type type) const;

    bool parse(const ParseArgs& args);

private:
    ASParamParser* makeParser(const ASParamParser::ParseArgs& args) const;

    agl::utl::ParameterList mList;
    sead::Buffer<ASParamParser*> mParsers;
};

class ASFrameCtrlParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASFrameCtrlParser, ASParamParser)
public:
    ASFrameCtrlParser() : ASParamParser(Type::FrameCtrl) {}

    const auto& getRate() const { return *mRate; }
    const auto& getStartFrame() const { return *mStartFrame; }
    const auto& getEndFrame() const { return *mEndFrame; }
    const auto& getLoopStopCount() const { return *mLoopStopCount; }
    const auto& getLoopStopCountRandom() const { return *mLoopStopCountRandom; }
    const auto& getReversePlay() const { return *mReversePlay; }
    const auto& getUseGlobalFrame() const { return *mUseGlobalFrame; }
    const auto& getConnect() const { return *mConnect; }
    const auto& getFootType() const { return *mFootType; }
    const auto& getAnmLoop() const { return *mAnmLoop; }

    bool parse(const ParseArgs& args) override;

private:
    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<float> mRate;
    agl::utl::Parameter<float> mStartFrame;
    agl::utl::Parameter<float> mEndFrame;
    agl::utl::Parameter<float> mLoopStopCount;
    agl::utl::Parameter<float> mLoopStopCountRandom;
    agl::utl::Parameter<bool> mReversePlay;
    agl::utl::Parameter<bool> mUseGlobalFrame;
    agl::utl::Parameter<int> mConnect;
    agl::utl::Parameter<int> mFootType;
    agl::utl::Parameter<int> mAnmLoop;
};

class ASTriggerEventsParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASTriggerEventsParser, ASParamParser)
public:
    struct Event {
        agl::utl::ParameterObj obj;
        int type_index;
        agl::utl::Parameter<float> frame;
        agl::utl::Parameter<sead::SafeString> value;
    };

    ASTriggerEventsParser() : ASParamParser(Type::TriggerEvents) {}
    ~ASTriggerEventsParser() override { mEvents.freeBuffer(); }
    ASTriggerEventsParser(const ASTriggerEventsParser&) = delete;
    auto operator=(const ASTriggerEventsParser&) = delete;

    const sead::Buffer<Event>& getEvents() const { return mEvents; }

    bool parse(const ParseArgs& args) override;

private:
    sead::Buffer<Event> mEvents;
};

class ASHoldEventsParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASHoldEventsParser, ASParamParser)
public:
    struct Event {
        agl::utl::ParameterObj obj;
        int type_index;
        agl::utl::Parameter<float> start_frame;
        agl::utl::Parameter<float> end_frame;
        agl::utl::Parameter<sead::SafeString> value;
    };

    ASHoldEventsParser() : ASParamParser(Type::HoldEvents) {}
    ~ASHoldEventsParser() override { mEvents.freeBuffer(); }
    ASHoldEventsParser(const ASHoldEventsParser&) = delete;
    auto operator=(const ASHoldEventsParser&) = delete;

    const sead::Buffer<Event>& getEvents() const { return mEvents; }

    bool parse(const ParseArgs& args) override;

private:
    sead::Buffer<Event> mEvents;
};

class ASStringArrayParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASStringArrayParser, ASParamParser)
public:
    struct Value {
        agl::utl::Parameter<sead::SafeString> value;
    };

    ASStringArrayParser() : ASParamParser(Type::StringArray) {}
    ~ASStringArrayParser() override { mValues.freeBuffer(); }
    ASStringArrayParser(const ASStringArrayParser&) = delete;
    auto operator=(const ASStringArrayParser&) = delete;

    const sead::Buffer<Value>& getValues() const { return mValues; }

    bool parse(const ParseArgs& args) override;

private:
    agl::utl::ParameterObj mObj;
    sead::Buffer<Value> mValues;
};

class ASRangesParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASRangesParser, ASParamParser)
public:
    struct Range {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<float> start;
        agl::utl::Parameter<float> end;
    };

    ASRangesParser() : ASParamParser(Type::Ranges) {}
    ~ASRangesParser() override { mRanges.freeBuffer(); }
    ASRangesParser(const ASRangesParser&) = delete;
    auto operator=(const ASRangesParser&) = delete;

    const sead::Buffer<Range>& getRanges() const { return mRanges; }

    bool parse(const ParseArgs& args) override;

private:
    sead::Buffer<Range> mRanges;
};

class ASFloatArrayParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASFloatArrayParser, ASParamParser)
public:
    struct Value {
        agl::utl::Parameter<float> value;
    };

    ASFloatArrayParser() : ASParamParser(Type::FloatArray) {}

    ~ASFloatArrayParser() override { mValues.freeBuffer(); }
    ASFloatArrayParser(const ASFloatArrayParser&) = delete;
    auto operator=(const ASFloatArrayParser&) = delete;

    const sead::Buffer<Value>& getValues() const { return mValues; }

    bool parse(const ParseArgs& args) override;

private:
    agl::utl::ParameterObj mObj;
    sead::Buffer<Value> mValues;
};

class ASIntArrayParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASIntArrayParser, ASParamParser)
public:
    struct Value {
        agl::utl::Parameter<int> value;
    };

    ASIntArrayParser() : ASParamParser(Type::IntArray) {}

    ~ASIntArrayParser() override { mValues.freeBuffer(); }
    ASIntArrayParser(const ASIntArrayParser&) = delete;
    auto operator=(const ASIntArrayParser&) = delete;

    const sead::Buffer<Value>& getValues() const { return mValues; }

    bool parse(const ParseArgs& args) override;

private:
    agl::utl::ParameterObj mObj;
    sead::Buffer<Value> mValues;
};

class ASBitIndexParser : public ASParamParser {
    SEAD_RTTI_OVERRIDE(ASBitIndexParser, ASParamParser)
public:
    ASBitIndexParser() : ASParamParser(Type::BitIndex) {}

    int getBitIndex() const { return mTypeIndex; }

    bool parse(const ParseArgs& args) override;

private:
    int mTypeIndex = -1;
};

}  // namespace ksys::res
