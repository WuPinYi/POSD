#ifndef SUBJECT_H
#define SUBJECT_H

#include <algorithm>
#include <vector>
#include "observer.h"

class Subject
{
    public:
        void attach(Observer* observer)
        {
            _observers.push_back(observer);
        }

        void detach(Observer* observer)
        {
            _observers.erase(find(_observers.begin(), _observers.end(), observer));
        }

        void notify()
        {
            for (std::vector<Observer*>::iterator iter = _observers.begin(); iter != _observers.end(); iter++)
            {
                (*iter)->update();
            }
        }
    private:
        std::vector<Observer*> _observers;
};
#endif
