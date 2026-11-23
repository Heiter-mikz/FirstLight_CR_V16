#pragma once

// Exact-build native probe offsets.  All absolute libg addresses, object
// offsets, vtable locations, call-site opcodes and hook prologues used by
// cr_replay_probe.cpp live here rather than in the probe implementation.
//
// V15 values are migrated verbatim from the previous V15 probe.
// V16 is intentionally empty until each address/layout is assigned to the
// V16 binary.  Zero means "unavailable"; it must never fall back to V15.

#include <cstddef>
#include <cstdint>

#ifndef CR_PROBE_TARGET_VERSION
#define CR_PROBE_TARGET_VERSION 15
#endif

namespace cr_probe_offsets {

struct OffsetTable {
  std::uintptr_t kReplayJsonSetterOffset;
  std::uintptr_t kReplayManagerGetterOffset;
  std::uintptr_t kLibgStringFromUtf8Offset;
  std::uintptr_t kNativeReplayRunnerOffset;
  std::uintptr_t kReplayBattleControllerLifecycleOffset;
  std::uintptr_t kReplayBattleControllerFullUpdateOffset;
  std::uintptr_t kReplayBattleControllerClockOffset;
  std::uintptr_t kReplayBattleControllerAlternateUpdateOffset;
  std::uintptr_t kReplayClockGlobalPauseGuardOffset;
  std::uintptr_t kGameAppGetterOffset;
  std::uintptr_t kGameAppPauseGuardOffset;
  std::uintptr_t kGameAppPendingEventSetterOffset;
  std::size_t kGameAppPendingEventFlagsOffset;
  std::size_t kGameAppPendingEventOffset;
  std::size_t kReplayBattleControllerStateOffset;
  std::size_t kReplayBattleControllerAccumulatorOffset;
  std::size_t kReplayBattleControllerSpeedOffset;
  std::size_t kReplayBattleControllerSuspendedOffset;
  std::uintptr_t kGameStateLoadOffset;
  std::uintptr_t kGameStateStepOffset;
  std::uintptr_t kGameStateTickOffset;
  std::uintptr_t kGameStateContextAOffset;
  std::uintptr_t kGameStateContextBOffset;
  std::uintptr_t kGameStateNewOffset;
  std::uintptr_t kGameStateDeleteOffset;
  std::uintptr_t kGameStateConstructorOffset;
  std::uintptr_t kGameStateSetupOffset;
  std::uintptr_t kGameStateDestroyOffset;
  std::uintptr_t kGameStateBaseDestroyOffset;
  std::uintptr_t kJsonParseOffset;
  std::uintptr_t kLogicCommandParseOffset;
  std::uintptr_t kLogicCommandAppendOffset;
  std::uintptr_t kLogicCommandQueueConstructorOffset;
  std::uintptr_t kLogicCommandQueueDestroyOffset;
  std::uintptr_t kStateSnapshotOffset;
  std::uintptr_t kStateSnapshotDeleteOffset;
  std::uintptr_t kByteStreamResetReadOffset;
  std::uintptr_t kByteStreamFlipReadOffset;
  std::uintptr_t kByteStreamResetChecksumOffset;
  std::uintptr_t kGameStateDeserializeHeaderOffset;
  std::uintptr_t kGameStateDeserializeBodyOffset;
  std::uintptr_t kCardSelectionBuildOffset;
  std::uintptr_t kJsonMemberFindOffset;
  std::uintptr_t kLogicDataByGlobalIdOffset;
  std::uintptr_t kLocationTileMapEnsureOffset;
  std::uintptr_t kLocationTileMapLookupOffset;
  std::uintptr_t kEglSwapBuffersGotOffset;
  std::uintptr_t kTranslatedSha256InitializerCallOffset;
  std::uint32_t kTranslatedSha256InitializerCall;
  std::uintptr_t kGameStateContextRootSlotOffset;
  std::uintptr_t kBuffAssetVtableOffset;
  std::uintptr_t kBuffAssetClassNameGetterOffset;
  std::uintptr_t kLogicDataTypeGetterOffset;
  std::uintptr_t kProjectileVtableOffset;
  std::uintptr_t kProjectileKindGetterOffset;
  std::uintptr_t kCharacterVtableOffset;
  std::size_t kProjectileDragStageOffset;
  std::size_t kProjectileDragBackSpeedOffset;
  std::uintptr_t kChampionControllerVtableOffset;
  std::uintptr_t kChampionActionDataVtableOffset;
  std::uintptr_t kCharacterAbilityDataVtableOffset;
  std::size_t kCharacterAbilityExtraSpawnBaseOffset;
  std::size_t kCharacterAbilityExtraSpawnLimitOffset;
  std::size_t kCharacterExtraSpawnAccumulatorOffset;
  std::uintptr_t kCaptureCharacterActionDataVtableOffset;
  std::uintptr_t kCaptureCharacterRuntimeVtableOffset;
  std::uintptr_t kThresholdRelocationActionDataVtableOffset;
  std::uintptr_t kThresholdRelocationRuntimeVtableOffset;
  std::uintptr_t kPeriodicAttackModifierActionDataVtableOffset;
  std::uintptr_t kPeriodicAttackModifierRuntimeVtableOffset;
  std::size_t kContentPostProcessReadyOffset;
};

struct SignatureTable {
  std::uint8_t kReplayJsonSetterPrologue[16];
  std::uint8_t kNativeReplayRunnerPrologue[16];
  std::uint8_t kReplayBattleControllerLifecyclePrologue[16];
  std::uint8_t kReplayBattleControllerFullUpdatePrologue[16];
  std::uint8_t kReplayBattleControllerClockPrologue[16];
  std::uint8_t kReplayBattleControllerAlternateUpdatePrologue[16];
  std::uint8_t kGameAppPendingEventSetterPrologue[16];
  std::uint8_t kGameStateLoadPrologue[16];
  std::uint8_t kGameStateStepPrologue[16];
};

struct ProbeProfile {
  const char *label;
  const char *apk_version;
  std::uint32_t apk_version_code;
  const char *libg_sha256;
  const char *libg_build_id;
  bool runner_hooks_ready;
  bool native_touch_hooks_ready;
  bool combat_event_hooks_ready;
  bool phase_runtime_hooks_ready;
  bool special_movement_hooks_ready;
  bool action_movement_hooks_ready;
  bool character_state_hooks_ready;
  bool visibility_hooks_ready;
  bool remaining_runtime_hooks_ready;
  bool tower_troop_hooks_ready;
  OffsetTable offsets;
  SignatureTable signatures;
};

inline constexpr ProbeProfile kV15Profile{
    "Null's Royale 15.535.13",
    "15.535.13",
    150535013u,
    "110aa2b5cac391c498645e072b0d88729428c2c2845e7e2737ca8ee979059783",
    "90e6f351f0dec4a28b494c3812d2629fd45d5a83",
    true, true, true, true, true, true, true, true, true, true,
  {
    0x00c8de8c,
    0x00c8c5b8,
    0x0138a800,
    0x00c87ecc,
    0x00c87620,
    0x00c88bbc,
    0x00c890bc,
    0x00c899e0,
    0x00cb6694,
    0x00755818,
    0x0075c628,
    0x0075a6dc,
    0x1b8,
    0x1bc,
    0x30,
    0x44,
    0x74,
    0x18c,
    0x01061b1c,
    0x010620a4,
    0x01062bc0,
    0x0080031c,
    0x00eaf1c8,
    0x017e4b20,
    0x017e4b50,
    0x01060ba8,
    0x01060f84,
    0x010610b0,
    0x00988844,
    0x0121a648,
    0x00d2fe78,
    0x00d2eef0,
    0x00d2eddc,
    0x00d2ee40,
    0x00ad9a50,
    0x0105e8bc,
    0x0121220c,
    0x0121221c,
    0x012141bc,
    0x010634c0,
    0x0106379c,
    0x00e2d1bc,
    0x00d0e100,
    0x00dd1340,
    0x00857608,
    0x00df8508,
    0x018e9d88,
    0x00c8ece0,
    0x97eba894u,
    0x019ad878,
    0x01882500,
    0x00d961f4,
    0x00dc2560,
    0x0189cc28,
    0x00f27a58,
    0x0189c4e8,
    0x189,
    0x1b0,
    0x0189e4e8,
    0x0188cb28,
    0x018823f0,
    0x104,
    0x108,
    0x1f0,
    0x0188c848,
    0x0189e2d8,
    0x0188ef18,
    0x0189f6f0,
    0x0188eac8,
    0x0189f3d8,
    0x6e8,
  },
  {
    { 0xfd, 0x7b, 0xbe, 0xa9, 0xf4, 0x4f, 0x01, 0xa9, 0xfd, 0x03, 0x00, 0x91, 0xf4, 0x03, 0x01, 0xaa },
    { 0xff, 0x03, 0x02, 0xd1, 0xfd, 0x7b, 0x02, 0xa9, 0xfb, 0x1b, 0x00, 0xf9, 0xfa, 0x67, 0x04, 0xa9 },
    { 0xff, 0x83, 0x03, 0xd1, 0xfd, 0x7b, 0x0a, 0xa9, 0xf8, 0x5f, 0x0b, 0xa9, 0xf6, 0x57, 0x0c, 0xa9 },
    { 0xff, 0x03, 0x02, 0xd1, 0xeb, 0x2b, 0x03, 0x6d, 0xe9, 0x23, 0x04, 0x6d, 0xfd, 0x7b, 0x05, 0xa9 },
    { 0x08, 0x30, 0x46, 0x39, 0x48, 0x00, 0x00, 0x34, 0xc0, 0x03, 0x5f, 0xd6, 0xff, 0x83, 0x03, 0xd1 },
    { 0xe8, 0x0f, 0x1e, 0xfc, 0xfd, 0xfb, 0x00, 0xa9, 0xf3, 0x0f, 0x00, 0xf9, 0xfd, 0x23, 0x00, 0x91 },
    { 0x08, 0xc0, 0x41, 0xb9, 0x09, 0xbc, 0x41, 0xb9, 0x1f, 0x01, 0x02, 0x6b, 0x08, 0xe0, 0x46, 0x39 },
    { 0xff, 0x83, 0x01, 0xd1, 0xfd, 0x7b, 0x01, 0xa9, 0xf9, 0x13, 0x00, 0xf9, 0xf8, 0x5f, 0x03, 0xa9 },
    { 0xfd, 0x7b, 0xbc, 0xa9, 0xf8, 0x5f, 0x01, 0xa9, 0xf6, 0x57, 0x02, 0xa9, 0xf4, 0x4f, 0x03, 0xa9 },
  }
};

inline constexpr ProbeProfile kV16Profile{
    "Null's Royale 16.635.1",
    "16.635.1",
    160635001u,
    "0b580222e5a3502cf153bb5e6297ec32d2b154b605b777c74873dd75722e4eaa",
    "179ac4bd38c205bc5041d372a79f1c2f929b1c30",
    false, false, false, false, false, false, false, false, false, false,
    {},
    {}
};

#if CR_PROBE_TARGET_VERSION == 15
inline constexpr const ProbeProfile &kSelectedProfile = kV15Profile;
#elif CR_PROBE_TARGET_VERSION == 16
inline constexpr const ProbeProfile &kSelectedProfile = kV16Profile;
#else
#error "CR_PROBE_TARGET_VERSION must be 15 or 16"
#endif

static_assert(kV15Profile.offsets.kGameStateContextRootSlotOffset == 0x019ad878);
static_assert(kV15Profile.offsets.kContentPostProcessReadyOffset == 0x6e8);
static_assert(kV16Profile.offsets.kGameStateContextRootSlotOffset == 0);
static_assert(kV16Profile.offsets.kContentPostProcessReadyOffset == 0);
static_assert(!kV16Profile.runner_hooks_ready);

} // namespace cr_probe_offsets
