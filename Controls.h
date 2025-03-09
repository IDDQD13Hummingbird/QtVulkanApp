#ifndef CONTROLS_H
#define CONTROLS_H

#include <qevent.h>

struct KeyState {
    bool W{0};
    bool A{0};
    bool S{0};
    bool D{0};
};
struct KeyState2 {
    bool Up{0};
    bool Left{0};
    bool Down{0};
    bool Right{0};
};

class Controls {
public:
    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *event) = 0;
};

#endif // CONTROLS_H
