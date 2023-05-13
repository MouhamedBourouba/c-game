#ifndef ECS_H
#define ECS_H

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename t>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
    Entity *entity;
    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};
    virtual ~Component(){};
};

class Entity
{
private:
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitset componentBitset;
    bool active;

public:
    bool isActive() { return active; }
    void update()
    {
        for (auto &c : components)
            c->update();
        for (auto &c : components)
            c->draw();
    }
    void draw() {}
    void destroy() { active = false; }
    template <typename T>
    bool hasComponent()
    {
        int typeID = getComponentTypeID<T>();
        return componentBitset[typeID];
    }
    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&...args)
    {
        T *component(new T(std::forward(args)...));
        component->entity = this;
        // TODO: remove uniq pointer
        std::unique_ptr<Component> uPtr({component});
        components.emplace_back(std::move(uPtr));
        componentArray[getComponentTypeID<T>()] = component;
        componentBitset[getComponentTypeID<T>()] = true;
        component->init();
        return *component;
    }
    template <typename T>
    T &getComponent()
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update()
    {
        for (auto &e : entities)
            e->update();
    }
    void draw()
    {
        for (auto &e : entities)
            e->draw();
    }
    void refresh()
    {
    }
    Entity &addEntity()
    {
        auto *e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

#endif