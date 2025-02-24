#include "Internal/Fixes/SewingMachineSoundFix.hpp"
#include "Internal/Config/Config.hpp"
#include "Internal/Utility/Utility.hpp"

// Sounds:
// EditorID = UIWorkshopSewingMachineRunLPM
// FormID = 0019E999

// Workbenches:
// EditorID = 
// FormID = 

namespace Internal::Fixes::SewingMachineSoundFix
{
	static inline constexpr std::string_view FixCommand = "ForceKillSound 0019E999"sv;

	void Install() noexcept
	{
		logger::info("Fix installing: SewingMachineSoundFix."sv);

		if (!Config::bSewingMachineSoundFix.GetValue()) {
			logger::info("Fix aborted: SewingMachineSoundFix. Reason: Fix was disabled in ini file."sv);
			return;
		}

		// register cellchange/load/furniture exit/etc listeners

		logger::info("Fix installed: SewingMachineSoundFix."sv);
	}

	void KillSound()
	{
		Utility::Console::ExecuteCommand(FixCommand, true);
	}

	namespace Events
	{
		namespace Cell
		{

		}

		namespace Furniture
		{

		}
	}
}
