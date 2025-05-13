#include "finder.hh"

using namespace pro2;
using namespace std;

#include "platform.hh"
#include "strawberry.hh"
template class Finder<Platform>;
template class Finder<Strawberry>;

// DISCLAIMER:
// NO ÉS LA VERSIÓ DEFINITIVA AMB TEMPS O(log n)

template <typename T>
void Finder<T>::add(T *t) {
    objects_.insert(t);
}

template <typename T>
void Finder<T>::remove(T *t) {
    objects_.erase(t);
}

template <typename T>
void Finder<T>::update(T *t) {
    remove(t);
    add(t);
}

template <typename T>
set<T*> Finder<T>::query(Rect rect) {
    set<T*> result;

    typename set<T*>::iterator it;
    for (it = objects_.begin(); it != objects_.end(); ++it) {
        T* obj = *it;
        const Rect& obj_rect = obj->get_rect();
        if (rects_overlap(rect, obj_rect)) {
            result.insert(obj);
        }
    }
    return result;
}