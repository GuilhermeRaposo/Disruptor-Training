#include "pch.h"
#include "DisruptorTraining.h"
#include "bakkesmod/wrappers/GameObject/RumbleComponent/RumblePickupComponentWrapper.h"



BAKKESMOD_PLUGIN(DisruptorTraining, "Enables a constant disruptor power-up on your car", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void DisruptorTraining::onLoad()
{
    _globalCvarManager = cvarManager;
    // !! Enable debug logging by setting DEBUG_LOG = true in logging.h !!
    DEBUGLOG("DisruptorTraining debug mode enabled");

    cvarManager->registerCvar("DisruptorTraining_enabled", "0", "Enable DisruptorTraining", true, true, 0, true, 1);
    gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", std::bind(&DisruptorTraining::onTick, this));
}

void DisruptorTraining::onTick()
{
    // Check if the plugin is enabled in the settings
    CVarWrapper enableCvar = cvarManager->getCvar("DisruptorTraining_enabled");
    if (!enableCvar) { return; }
    bool enabled = enableCvar.getBoolValue();
    if (!enabled) {
        return;
    }

    if (!gameWrapper->IsInGame())
    {
        return;
    }

    CarWrapper localCar = gameWrapper->GetLocalCar();
    if (!localCar) {
        return;
    }
    RBActorWrapper localActor = localCar;

    RumblePickupComponentWrapper pickup = localCar.GetAttachedPickup();

    if (pickup)
    {
        std::string pickupName = pickup.GetPickupName().ToString();
        if (pickupName == "EnemyBooster" && !pickup.GetbIsActive())
        {
            TargetedPickup targetedPickup(pickup.memory_address);
            targetedPickup.SetbCanTargetTeamCars(true);
            targetedPickup.SetClientTarget(localActor);
            targetedPickup.TryActivate(targetedPickup.GetClientTarget());
        }
    }
}

