#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <typeindex>

class ObjectManager
{
private:
    ObjectManager(){};
    std::unordered_map<std::type_index, std::unordered_set<void*>> objs;

public:
    static ObjectManager& get_instance(){
        static ObjectManager instance;
        return instance;
    }

    template<typename T>
    void track_object(T* t){
        if(objs.find(typeid(t)) == objs.end()){
            objs[typeid(t)] = std::unordered_set<void*>();
        }
        objs[typeid(t)].insert(static_cast<void*>(t));
    }

    template<typename T>
    void untrack_object(T* t){
        if(objs.find(typeid(t)) == objs.end()){
            std::cout << "obj is not being tracked anyway!" << std::endl;
            return;
        }
        auto t_set = objs[typeid(t)];
        if(t_set.find(static_cast<void*>(t)) == t_set.end()){
            std::cout << "obj is not being tracked anyway!" << std::endl;
            return;
        }
        t_set.erase(static_cast<void*>(t));
    }

    template<typename T>
    std::unordered_set<T*> get_objs(){
        T* t; // barbaric
        if(objs.find(typeid(t)) != objs.end()){
            std::unordered_set<T*> res;
            for(auto i : objs[typeid(t)]){
                res.insert(static_cast<T*>(i));
            }
            return res;
        }
        return std::unordered_set<T*>();
    } 

    std::unordered_map<std::type_index, std::unordered_set<void*>> get_map(){return objs;}

    ObjectManager(ObjectManager const&) = delete;
    void operator=(ObjectManager const&) = delete;
};


namespace core
{   

template<typename T>
static T* New(){
    T* t = new T();
    ObjectManager::get_instance().track_object(t);
    return t;
}

template<typename T>
static void Delete(T* t){
    ObjectManager::get_instance().untrack_object(t);
}

template<typename T>
static std::unordered_set<T*> get_objects(){
    return ObjectManager::get_instance().get_objs<T>();
}
}