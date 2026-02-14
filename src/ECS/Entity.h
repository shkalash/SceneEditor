#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Component.h"
#include "utils/uuid.h"

class Entity {
    public:
    const uint64_t uuid;
    std::string name;
    std::vector<std::unique_ptr<Component>> components;
    explicit Entity(const std::string& name) : uuid(generateUUID()), name(name) {}

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T* ptr = component.get();
            components.push_back(std::move(component));
            return ptr;
    }
    
    template<typename T>
    T* getComponent() const {
        for (const auto& comp : components) {
            if (comp->typeId == Component::getTypeId<T>()) {
                return static_cast<T*>(comp.get());
            }
        }
        return nullptr;
    }

    template<typename T>
    void removeComponent() {
        auto it = std::remove_if(components.begin(), components.end(),
            [](const std::unique_ptr<Component>& comp) {
                return comp->typeId == Component::getTypeId<T>();
            });
        components.erase(it, components.end());
    }

};
