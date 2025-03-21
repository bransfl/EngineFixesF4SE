#pragma once

namespace Internal::Fixes
{
	class ActorCauseSaveBloatFix
	{
	public:
		/**
		 * @brief Installs the fix.
		 */
		static void Install() noexcept;

	private:
		/**
		 * @brief Gathers all non-nullptr references with base formtype kPROJ.
		 * @param a_cell The cell to gather from. If this is null, an empty vector is returned.
		 * @return Vector of found references.
		 */
		static std::vector<RE::TESObjectREFR*> GetProjectilesInCell(RE::TESObjectCELL* a_cell);

		class CellAttachDetachEventHandler : public RE::BSTEventSink<RE::CellAttachDetachEvent>
		{
		public:
			[[nodiscard]] static CellAttachDetachEventHandler* GetSingleton()
			{
				static CellAttachDetachEventHandler singleton;
				return std::addressof(singleton);
			}

			RE::BSEventNotifyControl ProcessEvent(const RE::CellAttachDetachEvent& a_event, RE::BSTEventSource<RE::CellAttachDetachEvent>*) override
			{
				switch (*a_event.type) {
					case RE::CellAttachDetachEvent::EVENT_TYPE::kPreDetach: {
						if (!a_event.cell) {
							logger::warn("ActorCauseSaveBloatFix -> a_event.cell was nullptr. Skipping this cell."sv);
						}

						std::vector<RE::TESObjectREFR*> projectiles = GetProjectilesInCell(a_event.cell);
						logger::info("ActorCauseSaveBloatFix -> Processing projectiles vector. Size: {}."sv, projectiles.size());
						if (projectiles.size() == 0) {
							break;
						}
						else {
							for (RE::TESObjectREFR* proj : projectiles) {
								if (proj) {
									if (proj->GetActorCause() != nullptr) {
										proj->SetActorCause(nullptr);
									}
								}
							}
						}

						break;
					}
					default: {
						break;
					}
				}
				return RE::BSEventNotifyControl::kContinue;
			}

		private:
			CellAttachDetachEventHandler() = default;
			CellAttachDetachEventHandler(const CellAttachDetachEventHandler&) = delete;
			CellAttachDetachEventHandler(CellAttachDetachEventHandler&&) = delete;
			~CellAttachDetachEventHandler() = default;
			CellAttachDetachEventHandler& operator=(const CellAttachDetachEventHandler&) = delete;
			CellAttachDetachEventHandler& operator=(CellAttachDetachEventHandler&&) = delete;
		};
	};
}
