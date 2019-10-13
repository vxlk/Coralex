#ifndef POOL_H
#define POOL_H
#include <vector>
#include <string>

template <typename T>
class Pool
{
    std::vector<T> pool;
    unsigned long int index;
    std::string objName;
public:

    explicit Pool(std::string name) : pool(), index(0), objName(name) {}

    T getFromPool() noexcept;

    void addBack(T) noexcept;

    inline constexpr int getIndex() const noexcept { return this->index; }
    inline constexpr int getSize() const noexcept { return (int)this->pool.size(); }

};
#endif
