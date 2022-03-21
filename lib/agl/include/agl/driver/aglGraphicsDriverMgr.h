#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace agl {
class DrawContext;
class DisplayList;
}  // namespace agl

namespace agl::driver {

class GraphicsDriverMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(GraphicsDriverMgr)
public:
    GraphicsDriverMgr();
    virtual ~GraphicsDriverMgr();

    void waitDrawDone() const;
    void dumpInfo() const;
    void setPointLimits(agl::DrawContext* draw_context, float min, float max) const;
    void setPointSize(agl::DrawContext* draw_context, float point_size) const;
    void setLineWidth(agl::DrawContext* draw_context, float line_width) const;

    agl::DisplayList* getDefaultCommandBuffer();

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
    void genMessage(sead::hostio::Context* context) override;
#endif

protected:
    void initialize_(sead::Heap p_heap);

private:
    agl::DisplayList* mDefaultCommandBuffer;
    void* _30;
};

static_assert(sizeof(GraphicsDriverMgr) == 0x38);

}  // namespace agl::driver
