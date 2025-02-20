#include "Internal/Fixes/TransferManyItems/AddManyItemsFix.hpp"
#include "Internal/Config/Config.hpp"
#include "f4se_common/Relocation.h"
#include "f4se_common/SafeWrite.h"

namespace Internal::Fixes::TransferManyItems::AddManyItemsFix
{

	void Install() noexcept
	{
		logger::info("Fix installing: AddManyItems.");

		if (!Config::bAddManyItemsFix.GetValue()) {
			logger::info("Fix aborted: AddManyItems. Reason: Game version was NG.");
			return;
		}
		if (std::filesystem::exists("Data/F4SE/Plugins/AddFFFFFix.dll")) { // not a typo, their dll has 5 F's
			RE::ConsoleLog::GetSingleton()->PrintLine("EngineFixesF4SE - Mod 'Add FFFF Fix' was detected. It is recommended that you disable this mod while using EngineFixesF4SE.\n");
			logger::warn("Fix aborted: AddManyItems. Reason: Mod was installed: AddFFFFFix.dll.");
			return;
		}

		if (REL::Module::IsNG()) {
			// NG patch
			uint8_t buf[] = { 0x44, 0x8B, 0x44, 0x24, 0x70, 0x90 };
			SafeWriteBuf(RelocationManager::s_baseAddr + 0x004AEF51, buf, sizeof(buf));
		}
		else {
			// OG patch
			uint8_t buf[] = { 0x44, 0x8B, 0x44, 0x24, 0x74, 0x90 };
			SafeWriteBuf(RelocationManager::s_baseAddr + 0x003FBF3E, buf, sizeof(buf));
		}

		logger::info("Fix installed: AddManyItems.");
	}
}
