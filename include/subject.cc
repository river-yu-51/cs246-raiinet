export module Subject;

import <vector>;

import Observer;

export class Subject {
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = default;

    void notifyObservers();
    void attach(Observer*);
    void detach(Observer*);
};