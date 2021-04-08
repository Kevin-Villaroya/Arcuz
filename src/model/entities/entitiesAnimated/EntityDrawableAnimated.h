#ifndef __ENTITY_DRAWABLE_ANIMATED_H__
#define __ENTITY_DRAWABLE_ANIMATED_H__

#include "../EntityDrawable.h"
#include "../../../../viewer/animation/Animation.h"
#include <SFML/Network/Packet.hpp>

class EntityDrawableAnimated : public EntityDrawable{
    protected:
        std::vector<Animation> animations;
        std::vector<std::string> typeAnimations;

        virtual float getEntityScale() = 0;

        Animation* currentAnimation;
        unsigned int idCurrentAnimation;
    public:
        EntityDrawableAnimated();

        virtual void applySprite();
        void setDelayOfAnimation(unsigned int frames);

        void addAnimation(Animation animation, std::string typeAnimation);
        void clearAnimations();

        void playAnimation(std::string nameAnimation);

        bool update() override;

        Animation* getAnimation(std::string nameAnimation);
        const std::string& getNameAnimation() const;

        unsigned int convertNameAnimationToNumber(const std::string& name);
        std::string& convertNumberToNameAnimation(unsigned int number);

        void putIn(sf::Packet& packet) const override;
        void putOut(sf::Packet& packet) override;
};

#endif