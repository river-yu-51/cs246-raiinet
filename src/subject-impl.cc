module Subject;

import <algorithm>;

import Observer;
import Subject;

void Subject::notifyObservers() {
    for (auto *observer : observers) { observer->notify(); }
}

void Subject::attach(Observer* o) { observers.push_back(o); }

void Subject::detach(Observer* o) {
    auto it = std::remove(observers.begin(), observers.end(), o);
    observers.erase(it, observers.end());
}
