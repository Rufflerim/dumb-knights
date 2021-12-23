//
// Created by gaetz on 23/12/2021.
//

#ifndef ECS_COORDINATOR_H
#define ECS_COORDINATOR_H

#include <memory>
#include "../Defines.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace engine::ecs {
    class Coordinator {
        /// Initialize ECS coordination
        void init();


        // Entity methods

        /// Creates an entity
        /// \return Created entity ID
        Entity createEntity();

        /// Detroys an entity and remove its ECS system and component dependencies
        /// \param entity The entity we want to destroy
        void destroyEntity(Entity entity);


        // Component methods

        /// Register a component
        /// \tparam T Component class
        template<typename T>
        void registerComponent() {
            componentManager->registerComponent<T>();
        }

        /// Adds a component to a given entity and manage its signature
        /// \tparam T Component class
        /// \param entity Entity on which the component is added
        /// \param component Component we want to add
        template<typename T>
        void addComponent(Entity entity, T component) {
            componentManager->addComponent<T>(entity, component);

            auto signature = entityManager->getSignature(entity);
            signature.set(componentManager->getComponentType<T>(), true);
            entityManager->setSignature(entity, signature);

            systemManager->onEntitySignatureChanged(entity, signature);
        }

        /// Removes a component from a given entity and manage its signature
        /// \tparam T Component class
        /// \param entity Entity from which we want to remove a component
        template<typename T>
        void removeComponent(Entity entity) {
            componentManager->removeComponent<T>(entity);

            auto signature = entityManager->getSignature(entity);
            signature.set(componentManager->getComponentType<T>(), false);
            entityManager->setSignature(entity, signature);

            systemManager->onEntitySignatureChanged(entity, signature);
        }

        /// Get a specific component from an entity
        /// \tparam T Component class
        /// \param entity Targeted entity
        /// \return Reference to the given component
        template<typename T>
        T& getComponent(Entity entity) {
            return componentManager->getComponent<T>(entity);
        }

        /// Get a component ID from its class
        /// \tparam T Component class
        /// \return Component ID
        template<typename T>
        ComponentType getComponentType() {
            return componentManager->getComponentType<T>();
        }


        // System methods

        /// Register a system in order to use it
        /// \tparam T System type
        /// \return Shared pointer to the system
        template<typename T>
        std::shared_ptr<T> registerSystem() {
            return systemManager->registerSystem<T>();
        }

        template<typename T>
        void setSystemSignature(Signature signature) {
            systemManager->setSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
    };
}


#endif //ECS_COORDINATOR_H