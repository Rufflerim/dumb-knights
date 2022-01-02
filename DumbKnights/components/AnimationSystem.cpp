//
// Created by gaetz on 25/12/2021.
//

#include "AnimationSystem.h"
#include "Components.h"

void AnimationSystem::update(engine::ecs::Coordinator& coordinator, const GameTime& time) {
    for (auto& entity: entities) {
        auto& animator = coordinator.getComponent<Animator>(entity);
        auto& sprite = coordinator.getComponent<Sprite>(entity);

        // PLay state, make animation loop
        auto& currentRow = animator.animations.rows[animator.currentAnimRow];
        if (animator.state == AnimatorState::Play) {
            animator.timeCounter += time.dt;
            animator.frameIndex = animator.timeCounter / animator.animations.frameTime;
            u16 frameNumber = currentRow.frameNumber;
            if (animator.frameIndex >= frameNumber) {
                animator.frameIndex = 0;
                animator.timeCounter -= currentRow.frameNumber * animator.animations.frameTime;
            }
        }

        sprite.srcRect = gmath::Rectangle {
                Vec2 { static_cast<f32>(animator.frameIndex * animator.animations.frameWidth),
                       static_cast<f32>(animator.currentAnimRow * animator.animations.frameHeight) },
                Vec2 { static_cast<f32>(animator.animations.frameWidth),
                       static_cast<f32>(animator.animations.frameHeight) }};

        /*
        if (animator.)



        renderer.drawSprite(texture, gmath::Rectangle::nullRectangle, dstRect, transform.rotation,
                            sprite.origin, sprite.flip);
                            */
    }
}