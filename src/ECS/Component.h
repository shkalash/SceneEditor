#pragma once
#include <cstdint>

class Component {
    public:
        const uint32_t typeId;
        virtual ~Component() = default;

        // type identifier
        static uint32_t nextId() {
            static uint32_t id = 0;
            return id++;
        }

        // templating the type ID so the system can grow easily
        template <typename T>
        static uint32_t getTypeId() {
            static uint32_t typeId = nextId();
            return typeId;
        }

    protected:
        explicit Component(const uint32_t id) : typeId(id) {}

};

template<typename Derived>
class ComponentBase : public Component {
protected:
    ComponentBase() : Component(getTypeId<Derived>()) {}
};