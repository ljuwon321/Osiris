#include <Windows.h>

#include "../Config.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../SDK/Entity.h"
#include "../SDK/WeaponId.h"
#include "Triggerbot.h"

void Triggerbot::run(UserCmd* cmd) noexcept
{
    if (config.triggerbot.enabled) {
        const auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());

        const auto activeWeapon = interfaces.entityList->getEntityFromHandle(localPlayer->getProperty<int>("m_hActiveWeapon"));
            if (!activeWeapon || !getWeaponIndex(activeWeapon->getProperty<WeaponId>("m_iItemDefinitionIndex")))
                return;

        static auto lastTime = memory.globalVars->realtime;
        auto now = memory.globalVars->realtime;

        if ((GetAsyncKeyState(config.triggerbot.key) || !config.triggerbot.onKey)
            && now - lastTime >= config.triggerbot.shotDelay / 1000.0f) {
            auto inCrosshair = localPlayer->getProperty<int>("m_bHasDefuser", 92);
            if (inCrosshair > 0 && inCrosshair <= 64) {
                auto target = interfaces.entityList->getEntity(inCrosshair);
                if (target->isEnemy() && !target->getProperty<bool>("m_bGunGameImmunity")) {
                    constexpr int IN_ATTACK{ 1 };
                    cmd->buttons |= IN_ATTACK;
                }
            }
            lastTime = now;
        }
    }
}
