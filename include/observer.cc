export module Observer;
// contains: Observer

// Base Observer class for Observer pattern
export class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify() = 0;
};