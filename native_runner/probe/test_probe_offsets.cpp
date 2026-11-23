#include "probe_offsets.h"

using namespace cr_probe_offsets;

#if CR_PROBE_TARGET_VERSION == 15
static_assert(kSelectedProfile.apk_version_code == 150535013u);
static_assert(kSelectedProfile.runner_hooks_ready);
static_assert(kSelectedProfile.offsets.kReplayJsonSetterOffset == 0x00c8de8c);
static_assert(kSelectedProfile.offsets.kGameStateContextRootSlotOffset == 0x019ad878);
static_assert(kSelectedProfile.offsets.kContentPostProcessReadyOffset == 0x6e8);
#elif CR_PROBE_TARGET_VERSION == 16
static_assert(kSelectedProfile.apk_version_code == 160635001u);
static_assert(!kSelectedProfile.runner_hooks_ready);
static_assert(!kSelectedProfile.native_touch_hooks_ready);
static_assert(!kSelectedProfile.combat_event_hooks_ready);
static_assert(!kSelectedProfile.phase_runtime_hooks_ready);
static_assert(!kSelectedProfile.special_movement_hooks_ready);
static_assert(!kSelectedProfile.action_movement_hooks_ready);
static_assert(!kSelectedProfile.character_state_hooks_ready);
static_assert(!kSelectedProfile.visibility_hooks_ready);
static_assert(!kSelectedProfile.remaining_runtime_hooks_ready);
static_assert(!kSelectedProfile.tower_troop_hooks_ready);
static_assert(kSelectedProfile.offsets.kReplayJsonSetterOffset == 0);
static_assert(kSelectedProfile.offsets.kGameStateContextRootSlotOffset == 0);
static_assert(kSelectedProfile.offsets.kContentPostProcessReadyOffset == 0);
#else
#error Unsupported probe target
#endif

int main() { return 0; }
