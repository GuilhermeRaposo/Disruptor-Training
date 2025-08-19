#include "pch.h"
#include "DisruptorTraining.h"

void DisruptorTraining::RenderSettings() {
	CVarWrapper enableCvar = cvarManager->getCvar("DisruptorTraining_enabled");
	if (!enableCvar) { return; }
	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}

	CVarWrapper boostSpeedCvar = cvarManager->getCvar("DisruptorTraining_boostSpeed");
	if (!boostSpeedCvar) { return; }
	float boostSpeed = boostSpeedCvar.getFloatValue();
	if (ImGui::SliderFloat("Boost Speed", &boostSpeed, 0.0, 10000.0)) {
		boostSpeedCvar.setValue(boostSpeed);
	}

	ImGui::Separator();
	ImGui::TextUnformatted("For this to work properly you need to disable all power-ups except disruptor in the Rumble freeplay plugin");
}