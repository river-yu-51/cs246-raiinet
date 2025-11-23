export module Observer;

export class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify() = 0;
};