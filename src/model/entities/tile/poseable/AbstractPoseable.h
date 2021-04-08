#ifndef __ABSTRACT_POSEABLE_H__
#define __ABSTRACT_POSEABLE_H__

#include "../../entitiesAnimated/EntityDrawableAnimated.h"

class AbstractPoseable : public EntityDrawableAnimated{
private:
    bool recoverable;
    bool traversable ;
public:
    static AbstractPoseable EMPTY_POSEABLE;

    virtual float getEntityScale() override;
    AbstractPoseable(const std::string& name);
    AbstractPoseable(const std::string& name, bool traversable , bool recoverable);

    bool isRecoverable();
    void setRecoverable(bool recoverable);
    bool isTraversable ();

    std::string getName();
};

#endif