#pragma once

#include <gfx/seadColor.h>
#include <math/seadBoundBox.h>

namespace sead
{
class Viewport;
class Camera;
class Projection;
class DrawContext;

class TextWriter
{
public:
    virtual ~TextWriter();

    void printImpl_(const char*, int, bool, BoundBox2f*);
    void printf(const char* format, ...);
    void printf(const char16_t* format, ...);
    void setScaleFromFontHeight(float scale);
    void setCursorFromTopLeft(const Vector2f& pos);
    void beginDraw();
    static void setupGraphics(DrawContext* context);

    Viewport* mViewport;
    Projection* mProjection;
    Camera* mCamera;
    int _20;
    int _24;
    int _28;
    int _2c;
    Vector2f mScale;
    Color4f mColor;
    int _48;
    float mLineSpace;
    BoundBox2f mBoundBox2;
    int TextWriter_x58;
    int TextWriter_x5C;
    char16_t* mFormatBuffer;
    int mFormatBufferSize;
    int _6c;
    DrawContext* mDrawContext;
};
}  // namespace sead
