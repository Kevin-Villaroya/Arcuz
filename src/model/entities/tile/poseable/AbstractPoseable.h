#ifndef __ABSTRACT_POSEABLE_H__
#define __ABSTRACT_POSEABLE_H__

#include "../../entitiesAnimated/EntityDrawableAnimated.h"

class AbstractPoseable : public EntityDrawableAnimated{
private:
    bool recoverable;
    bool traversable ;
public:
    static AbstractPoseable EMPTY_POSEABLE;
    static std::vector<std::string> typePoseable;

    static AbstractPoseable* getAbstractPosable(const std::string& namePoseable);

    virtual float getEntityScale() override;
    AbstractPoseable(const std::string& name);
    AbstractPoseable(const std::string& name, bool traversable , bool recoverable);

    bool isRecoverable();
    void setRecoverable(bool recoverable);
    bool isTraversable ();

    void setCollisionPosition(float x, float y);
    void setCollisionPosition(const sf::Vector2f &postion);

    std::string getName();
};

#endif