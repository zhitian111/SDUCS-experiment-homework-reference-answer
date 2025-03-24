#include <iostream>

template<class T>
class queue
{
public:

    virtual ~queue() = 0;

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T& front() = 0;

    virtual const T& front() const = 0;

    virtual T& back() = 0;

    virtual const T& back() const = 0;

    virtual void pop() = 0;

    virtual void push(const T& theElement) = 0;

};

template<class T>
class extend_queue : public queue<T>
{

};