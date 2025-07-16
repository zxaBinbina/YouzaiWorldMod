#include "mod/youzaiworld.h"

#include "ll/api/mod/RegisterHelper.h"

namespace youzaiworld {

youzaiworld& youzaiworld::getInstance() {
    static youzaiworld instance;
    return instance;
}

bool youzaiworld::load() {
    getSelf().getLogger().debug("YouzaiWorldMod 加载中...");
    // Code for loading the mod goes here.
    return true;
}

bool youzaiworld::enable() {
    getSelf().getLogger().debug("YouzaiWorldMod 启用中...");
    // Code for enabling the mod goes here.
    return true;
}

bool youzaiworld::disable() {
    getSelf().getLogger().debug("YouzaiWorldMod 禁用中...");
    // Code for disabling the mod goes here.
    return true;
}

} 

LL_REGISTER_MOD(youzaiworld::youzaiworld, youzaiworld::youzaiworld::getInstance());
