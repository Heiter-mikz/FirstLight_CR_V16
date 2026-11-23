#include "probe_offsets.h"

using namespace cr_probe_offsets;

#if CR_PROBE_TARGET_VERSION == 15
static_assert(kSelectedProfile.apk_version_code == 150535013u);
static_assert(kSelectedProfile.runtime_offsets_ready);
static_assert(kSelectedProfile.offsets.kReplayJsonSetterOffset == 0x00c8de8c);
static_assert(kSelectedProfile.offsets.kGameStateContextRootSlotOffset == 0x019ad878);
static_assert(kSelectedProfile.offsets.kContentPostProcessReadyOffset == 0x6e8);
#elif CR_PROBE_TARGET_VERSION == 16
static_assert(kSelectedProfile.apk_version_code == 160635001u);
static_assert(!kSelectedProfile.runtime_offsets_ready);
static_assert(kSelectedProfile.offsets.kReplayJsonSetterOffset == 0);
static_assert(kSelectedProfile.offsets.kGameStateContextRootSlotOffset == 0);
static_assert(kSelectedProfile.offsets.kContentPostProcessReadyOffset == 0);
#else
#error Unsupported probe target
#endif

int main() { return 0; }
