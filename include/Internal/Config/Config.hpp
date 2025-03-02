#pragma once

namespace Internal::Config
{
	void Load() noexcept;

	// default is false in case a fix is removed from the ini for any reason

	// FIXES
	inline const auto bApplySpellsFix = REX::INI::Bool{ "Fixes"sv, "bApplySpellsFix"sv, false };

	inline const auto bBasherFix = REX::INI::Bool{ "Fixes"sv, "bBasherFix"sv, false };

	inline const auto bAddManyItemsFix = REX::INI::Bool{ "Fixes"sv, "bAddManyItemsFix"sv, false };

	inline const auto bDropManyItemsFix = REX::INI::Bool{ "Fixes"sv, "bDropManyItemsFix"sv, false };

	inline const auto bCombatMusicFix = REX::INI::Bool{ "Fixes"sv, "bCombatMusicFix"sv, false };

	inline const auto bEncounterZoneResetFix = REX::INI::Bool{ "Fixes"sv, "bEncounterZoneResetFix"sv, false };

	inline const auto bGrenadeMovementSpeedFix = REX::INI::Bool{ "Fixes"sv, "bGrenadeMovementSpeedFix"sv, false };

	inline const auto bLeveledListCrashFix = REX::INI::Bool{ "Fixes"sv, "bLeveledListCrashFix"sv, false };

	inline const auto bMagicEffectConditionsFix = REX::INI::Bool{ "Fixes"sv, "bMagicEffectConditionsFix"sv, false };


	inline const auto bWorkbenchSoundFix = REX::INI::Bool{ "Fixes"sv, "bWorkbenchSoundFix"sv, false };

	// PATCHES
	// n/a

	// WARNINGS
	inline const auto bDupeAddonNodesWarning = REX::INI::Bool{ "Warnings"sv, "bDupeAddonNodesWarning"sv, false };

	inline const auto bLeveledListEntryCountWarning = REX::INI::Bool{ "Warnings"sv, "bLeveledListEntryCountWarning"sv, false };
}
