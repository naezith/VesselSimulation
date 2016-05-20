#pragma once

#include <unordered_map>
#include "VesselSimLib/IShip.h"

namespace vsl {
	class VESSELSIMULATION_API VesselManager {
	public:
		VesselManager();
		~VesselManager();

		virtual void init();
		virtual void update(float _dt);

		IShip* requestNewVessel(std::string type);
		IShip* getVessel(int id);
		void deleteVessel(int id);
		void clearAll();

	private:
		std::unordered_map<int, IShip*> m_vessels;
		int available_id;
	};
}