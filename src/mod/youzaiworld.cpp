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
#include <mc/server/ServerInstance.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/MinecraftCommands.h>
#include <mc/world/actor/player/Player.h>


namespace youzaiworld {

struct YouzaiworldTagCommand {
    std::string tagType; // 字符串形式接收参数
    bool        value;   // 布尔值参数
};

void registerYouzaiworldCommand() {
    using namespace ll::command;
    auto& command =
        CommandRegistrar::getInstance().getOrCreateCommand("youzaiworld", "§4 (危险命令) §e悠哉世界服务器管理§r");

    // 注册子命令"tag"
    command.overload<YouzaiworldTagCommand>()
        .text("tag")
        .required("tagType") // 接收字符串参数
        .required("value")   // 接收布尔值参数
        .execute([](CommandOrigin const& origin, CommandOutput& output, YouzaiworldTagCommand const& param) {
            // 检查玩家权限（可选）
            if (origin.getOriginType() != CommandOriginType::Player) {
                output.error("该命令只能由玩家执行");
                return;
            }

            // 获取执行命令的玩家
            auto* entity = origin.getEntity();
            auto* player = dynamic_cast<Player*>(entity);
            if (!player) {
                output.error("无法获取玩家信息");
                return;
            }

            // 手动转换字符串参数
            std::string normalizedTag = param.tagType;
            std::transform(normalizedTag.begin(), normalizedTag.end(), normalizedTag.begin(), ::tolower);

            // 验证参数有效性
            if (normalizedTag != "nocjqscinf" && normalizedTag != "nocjjginf") { // 在这里添加更多标签类型
                output.error("无效的标签类型！请使用 nocjqscinf 或 nocjjginf");
                return;
            }

            // 测试命令可用性输出
            output.success("§e悠哉世界§7 >>>> §2命令执行成功! \n §w类型: {}, 值: {}", normalizedTag, param.value);

            
        });
}

youzaiworld& youzaiworld::getInstance() {
    static youzaiworld instance;
    return instance;
}

bool youzaiworld::load() {
    getSelf().getLogger().debug("YouzaiWorldMod 加载中...");
    // 加载逻辑
    return true;
}

bool youzaiworld::enable() {
    getSelf().getLogger().debug("YouzaiWorldMod 启用中...");
    registerYouzaiworldCommand();
    return true;
}

bool youzaiworld::disable() {
    getSelf().getLogger().debug("YouzaiWorldMod 禁用中...");
    // 禁用逻辑
    return true;
}

} // namespace youzaiworld

LL_REGISTER_MOD(youzaiworld::youzaiworld, youzaiworld::youzaiworld::getInstance());