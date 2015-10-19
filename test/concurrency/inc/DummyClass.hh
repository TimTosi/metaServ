#ifndef         DUMMYCLASS_HH_
# define        DUMMYCLASS_HH_

class           DummyClass
{
private:
    int         _nb;

public:
    DummyClass();
    ~DummyClass() = default;
    void        dummyFunc1(void) const;
    void        dummyFunc2(int &nb);
};

#endif          /* !DUMMYCLASS_HH_ */