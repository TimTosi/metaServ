#include        <iostream>
#include        "DummyClass.hh"

DummyClass::DummyClass()
:_nb(5)
{

}

void            DummyClass::dummyFunc1(void) const
{
    std::cout << "This is a task executed from a member function with signature T::void func(void) const" << std::endl;
}

void            DummyClass::dummyFunc2(int &nb)
{
    _nb = nb;
    std::cout << "This is a task executed from a member function with signature T::void func(void) const" << std::endl;
}