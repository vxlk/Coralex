#include "viewport.h"
#include "pool.h"
#include "bullet.h"

//fight me xiang
//it's technically a class
struct HUD final
{
    HUD() = default;
    HUD(HUD&) = default;
    HUD(HUD&&) = default;

    inline static void drawPool(const Pool<Bullet>& p)
    {
        Viewport::getInstance().drawPool(p.getIndex(), p.getSize());
    }
    static void draw();
};
