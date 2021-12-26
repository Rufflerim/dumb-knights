//
// Created by gaetz on 24/12/2021.
//

#ifndef SCENE_GAMEMAP_H
#define SCENE_GAMEMAP_H

#include <SDL_render.h>
#include "IScene.h"
#include "../components/RenderingSystem.h"

namespace scene {
    class GameMap : public IScene {
    public:
        explicit GameMap(engine::ecs::Coordinator& coordinator);

        void onInit() override;

        void onClose() override;

        void activate() override;

        void inactivate() override;

        void update(GameTime time) override;

        void draw(SDL_Renderer *pRenderer) override;

    private:
        std::shared_ptr<RenderingSystem> rendering;
        std::vector<Entity> entities { 100 };

    };
}

#endif //SCENE_GAMEMAP_H