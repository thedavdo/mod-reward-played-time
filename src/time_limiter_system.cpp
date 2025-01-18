// Time Limiter system made by Davdo, heavily adapted and modified from: Reward system made by Talamortis

#include "Configuration/Config.h"
#include "Player.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "Chat.h"

class time_limiter_system : public PlayerScript
{

public:
    time_limiter_system() : PlayerScript("time_limiter_system") {}

    uint32 curfewStart = sConfigMgr->GetOption<uint32>("TimeLimiterSystemCurfewStart", 24);
    uint32 curfewEnd = sConfigMgr->GetOption<uint32>("TimeLimiterSystemCurfewEnd", 24);

    void OnLogin(Player *player) override
    {
        if (!sConfigMgr->GetOption<bool>("TimeLimiterSystemEnable", true) && sConfigMgr->GetOption<bool>("TimeLimiterSystemAnnounce", true))
        {
            return;
        }

        ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00BingBong Time Limiter |rmodule. Curfew is set to start at %u:00 and ends at %u:00.", curfewStart, curfewEnd);
    }

    void OnBeforeUpdate(Player *player, uint32 p_time) override
    {
        if (!sConfigMgr->GetOption<bool>("TimeLimiterSystemEnable", true))
            return;

        uint32 currentHours = Acore::Time::GetHours();

        if(currentHours >= curfewStart || currentHours < curfewEnd) {
            ChatHandler(player->GetSession()).SendSysMessage("The server has reached its curfew. GO TO BED. Please come back tomorrow at %u:00.", curfewEnd);
            player->KickPlayer();
            return
        }

        if((curfewStart - currentHours) <= 1 && (curfewStart - currentHours) > 0) {
            ChatHandler(player->GetSession()).SendSysMessage("Curfew is in 1 hour. Please finish up and go to bed.");
        }

    }
};

class time_limiter_system_conf : public WorldScript
{
public:
    time_limiter_system_conf() : WorldScript("time_limiter_system_conf") {}
};

void AddTimeLimiterSystemScripts()
{
    new time_limiter_system();
    new time_limiter_system_conf();
}
