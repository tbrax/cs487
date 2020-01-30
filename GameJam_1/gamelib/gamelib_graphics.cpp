#include "pch.h"
#include <gamelib_locator.hpp>
#include <gamelib_graphics.hpp>

namespace GameLib {

    Graphics::Graphics(Context* ctx) { context = ctx; }

    Graphics::~Graphics() {}

    void Graphics::draw(int tileSetId, int tileId, float x, float y) { draw(tileSetId, tileId, (int)x, (int)y); }

    void Graphics::draw(int tileSetId, int tileId, int x, int y) {
        auto tileImage = context->getTileFast(tileSetId, tileId);
        if (!tileImage)
            return;
        context->drawTexture({ x, y }, { tileImage->w, tileImage->h }, tileImage->texture);
    }
}
