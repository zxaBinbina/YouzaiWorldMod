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

    struct YouzaiworldTagCommand {
        std::string tagType; // 字符串形式接收参数
        bool value;          // 布尔值参数
    };

    void registerYouzaiworldCommand() {
        using namespace ll::command;
        auto& command = CommandRegistrar::getInstance().getOrCreateCommand(
            "youzaiworld", 
            "Manage Youzaiworld tags"
        );
    
        // 注册子命令"tag"
        command.overload<YouzaiworldTagCommand>()
            .text("tag")
            .required("tagType")  // 接收字符串参数
            .required("value")    // 接收布尔值参数
            .execute(
                [](CommandOrigin const& origin, CommandOutput& output, YouzaiworldTagCommand const& param) {
                    // 检查玩家权限（可选）
                    if (origin.getOriginType() != CommandOriginType::Player) {
                        output.error("该命令只能由玩家执行");
                        return;
                    }
                    
                    // 手动转换字符串参数
                    std::string normalizedTag = param.tagType;
                    std::transform(normalizedTag.begin(), normalizedTag.end(), normalizedTag.begin(), ::tolower);
                    
                    // 验证参数有效性
                    if (normalizedTag != "nocjqscinf" && normalizedTag != "nocjjginf") {
                        output.error("无效的标签类型！请使用 nocjqscinf 或 nocjjginf");
                        return;
                    }
                    
                    // 这里可以添加您的业务逻辑
                    // 例如：更新玩家标签状态
                    
                    output.success("标签已更新！类型: {}, 值: {}", normalizedTag, param.value);
                }
            );
    }

    youzaiworld& youzaiworld::getInstance() {
        static youzaiworld instance;
        return instance;
    }

    bool youzaiworld::load()  {
        getSelf().getLogger().debug("YouzaiWorldMod 加载中...");
        // 加载逻辑
        return true;
    }

    bool youzaiworld::enable()  {
        getSelf().getLogger().debug("YouzaiWorldMod 启用中...");
        registerYouzaiworldCommand();
        return true;
    }

    bool youzaiworld::disable()  {
        getSelf().getLogger().debug("YouzaiWorldMod 禁用中...");
        // 禁用逻辑
        return true;
    }

} // namespace youzaiworld

LL_REGISTER_MOD(youzaiworld::youzaiworld, youzaiworld::youzaiworld::getInstance());