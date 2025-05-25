#include "finder.hh"

using namespace pro2;
using namespace std;

#include "platform.hh"
template class Finder<Platform>;
#include "strawberry.hh"
template class Finder<Strawberry>;

template <typename T>
void Finder<T>::add(T *t) {
    Rect rect = t->get_rect();
    obj_rect_map_[t] = rect;

    // Afegir al mapa de coordenades X inicials
    x_start_map_[rect.left].insert(t);
    
    // Afegir al mapa de coordenades X finals
    x_end_map_[rect.right].insert(t);
}

template <typename T>
void Finder<T>::remove(T *t) {
    // Si existeix
    auto it = obj_rect_map_.find(t);
    if (it != obj_rect_map_.end()) {
        Rect rect = it->second;
        
        // Elimina l'objecte del mapa de coordenades X inicials
        x_start_map_[rect.left].erase(t);
        if (x_start_map_[rect.left].empty()) {
            x_start_map_.erase(rect.left);
        }
        
        // Elimina l'objecte del mapa de coordenades X finals
        x_end_map_[rect.right].erase(t);
        if (x_end_map_[rect.right].empty()) {
            x_end_map_.erase(rect.right);
        }
    }

    // Elimina del mapa de rectangles
    obj_rect_map_.erase(t);
}

template <typename T>
void Finder<T>::update(T *t) {
    remove(t);
    add(t);
}

template <typename T>
set<T*> Finder<T>::query(pro2::Rect rect) {
    set<T*> result;
    
    // Troba objectes on el seu 'right' és >= rect.left
    typename map<int, set<T*>>::iterator it = x_end_map_.lower_bound(rect.left);
    for (; it != x_end_map_.end() && it->first <= rect.right; ++it) {
        for (T* obj : it->second) {
            Rect obj_rect = obj->get_rect();
            // Comprova que no estigui ni més a dalt ni més a baix
            if (obj_rect.top <= rect.bottom && obj_rect.bottom >= rect.top) {
                result.insert(obj);
            }
        }
    }

    // Troba objectes on el seu 'left' és >= rect.left
    typename map<int, set<T*>>::iterator it2 = x_start_map_.lower_bound(rect.left);
    for (; it2 != x_start_map_.end() && it2->first <= rect.right; ++it2) {
        for (T* obj : it2->second) {
            Rect obj_rect = obj->get_rect();
            // Comprova que no estigui ni més a dalt ni més a baix
            if (obj_rect.top <= rect.bottom && obj_rect.bottom >= rect.top) {
                result.insert(obj);
            }
        }
    }
    
    return result;
}