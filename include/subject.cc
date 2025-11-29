export module Subject;
// contains: Subject

import <vector>;

import Observer;

// Base Subject class for Observer pattern
export class Subject {
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = default;

    void notifyObservers();
    void attach(Observer *observer);
    void detach(Observer *observer);
};