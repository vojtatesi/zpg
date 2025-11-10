#pragma once
#include <vector>
#include <memory>
#include "IResizeObserver.h"

class IResizeSubject {
public:
    virtual ~IResizeSubject() = default;

    void addObserver(const std::shared_ptr<IResizeObserver>& obs) {
        observers.push_back(obs);
    }

protected:
    void notifyResize(int width, int height) {
        for (auto& obs : observers)
            if (obs) obs->onResize(width, height);
    }

private:
    std::vector<std::shared_ptr<IResizeObserver>> observers;
};
