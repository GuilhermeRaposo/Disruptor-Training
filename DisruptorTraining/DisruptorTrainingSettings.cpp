#include "pch.h"
#include "DisruptorTraining.h"

void DisruptorTraining::RenderSettings() {
	CVarWrapper enableCvar = cvarManager->getCvar("DisruptorTraining_enabled");
	if (!enableCvar) { return; }
	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}

	ImGui::TextUnformatted("For this to work properly you need to disable all power-ups except disruptor in the Rumble freeplay plugin");
}