#include "mod/youzaiworld.h"

#include "ll/api/mod/RegisterHelper.h"

#include <ll/api/Config.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerUseItemEvent.h>
#include <ll/api/service/Bedrock.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>
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
    auto& registrar = ll::command::CommandRegistrar::getInstance();
    auto& cmd = registrar.getOrCreateCommand(
        "youzaiworld", 
        "YouZaiWorld command system", 
        CommandPermissionLevel::Any
    );

    cmd.overload<CommandRawText, CommandRawText, bool>(getSelf())
        .required("tag")       // 一级子命令
        .required("subcommand") // 二级子命令
        .required("value")     // bool 参数
        .execute([](CommandOrigin const& origin, CommandOutput& output, 
                  CommandRawText const& tag, 
                  CommandRawText const& subCmd, 
                  bool value) {
            
            // 使用 mText 成员获取字符串
            std::string tagStr = tag.mText;
            std::string subCmdStr = subCmd.mText;
            
            // 验证一级子命令
            if (tagStr != "tag") {
                output.error("First subcommand must be 'tag'");
                return;
            }
            
            // 验证二级子命令
            if (subCmdStr != "nosxinf" && subCmdStr != "nocjinf") {
                output.error("Invalid subcommand. Use 'nosxinf' or 'nocjinf'");
                return;
            }
            
            // 检查执行者是否为玩家
            auto* entity = origin.getEntity();
            if (!entity || !entity->isType(ActorType::Player)) {
                output.error("Only players can use this command");
                return;
            }
            
            auto* player = static_cast<Player*>(entity);
            
            // 发送成功消息
            output.success(fmt::format(
                "{} set {} to {}",
                player->getRealName(),
                subCmdStr,
                value ? "true" : "false"
            ));
        });
    return true;
}

bool youzaiworld::disable() {
    getSelf().getLogger().debug("YouzaiWorldMod 禁用中...");
    // Code for disabling the mod goes here.
    return true;
}

} 

LL_REGISTER_MOD(youzaiworld::youzaiworld, youzaiworld::youzaiworld::getInstance());
