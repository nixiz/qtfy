#ifndef ICOMPOSITEINTERFACE_H
#define ICOMPOSITEINTERFACE_H

#include <qtfy.hpp>

class IInterface1
{
public:
    virtual void Interface1foo() = 0;
};
//SAVE_INTERFACE(IInterface1);

class IInterface2
{
public:
    virtual void Interface2foo() = 0;
};
//SAVE_INTERFACE(IInterface2);

#endif // ICOMPOSITEINTERFACE_H
