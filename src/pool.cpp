#include "pool.h"
#include "bullet.h"

template <typename T>
T Pool<T>::getFromPool() noexcept
{
    if (this->pool.empty()) 
    {
        T newObj(objName);
        pool.emplace_back(newObj);
		return pool[index];
    }
    
    if (index == 0)
    {
        T newObj(objName);
        pool.emplace_back(newObj);
    }
    if (index) --index;
    return pool[index];
    
}

template <typename T>
void Pool<T>::addBack(T b) noexcept
{
    this->pool[index] = b;
    ++index;
}

template class Pool<Bullet>;
