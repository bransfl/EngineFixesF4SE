#pragma once

namespace Internal::Fixes
{
	class StolenPowerArmorOwnershipFix
	{
	public:
		static void Install() noexcept;

	private:
		static void FixOwnership(RE::TESObjectREFR* a_ref);

		class FurnitureEventHandler : public RE::BSTEventSink<RE::TESFurnitureEvent>
		{
		public:
			[[nodiscard]] static FurnitureEventHandler* GetSingleton()
			{
				static FurnitureEventHandler singleton;
				return std::addressof(singleton);
			}

			virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) override
			{
				if (!a_event.actor.get() || a_event.actor.get() != RE::PlayerCharacter::GetSingleton()) {
					return RE::BSEventNotifyControl::kContinue;
				}

				// just incase the player hasnt used power armor yet
				if (!RE::PlayerCharacter::GetSingleton()->lastUsedPowerArmor.get() || !RE::PlayerCharacter::GetSingleton()->lastUsedPowerArmor.get().get()) {
					return RE::BSEventNotifyControl::kContinue;
				}

				RE::TESObjectREFR* furn = a_event.targetFurniture.get();
				if (!furn) {
					return RE::BSEventNotifyControl::kContinue;
				}

				if (furn == RE::PlayerCharacter::GetSingleton()->lastUsedPowerArmor.get().get()) {
					logger::info(FMT_STRING("StolenPowerArmorOwnershipFix -> FixOwnership() running on furniture: (FormID {:08X}, EditorID: {})."sv),
						furn->GetFormID(), furn->GetBaseObject()->GetFormEditorID());
					FixOwnership(furn);
				}

				return RE::BSEventNotifyControl::kContinue;
			}

			FurnitureEventHandler() = default;
			FurnitureEventHandler(const FurnitureEventHandler&) = delete;
			FurnitureEventHandler(FurnitureEventHandler&&) = delete;
			~FurnitureEventHandler() = default;
			FurnitureEventHandler& operator=(const FurnitureEventHandler&) = delete;
			FurnitureEventHandler& operator=(FurnitureEventHandler&&) = delete;
		};
	};
}
