#pragma once

class IResizeObserver {
public:
    virtual ~IResizeObserver() = default;
    virtual void onResize(int width, int height) = 0;
};
