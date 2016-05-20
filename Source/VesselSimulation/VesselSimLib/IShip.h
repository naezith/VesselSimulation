#pragma once

#include "VesselSimLib/Utility.h"
#include "VesselSimLib/IController.h"
#include "VesselSimLib/IPlayer.h"
#include <vector>

namespace vsl {
	class VESSELSIMULATION_API IShip : public vsl::IController {
	public:
		IShip() = default;
		~IShip() = default;

		virtual void init(vsl::Vector _pos, vsl::Vector _rot) = 0;
		virtual void update(float _dt) = 0;
		virtual vsl::Vector getPosition() = 0;
		virtual vsl::Vector getRotation() = 0;
		
		void setPlayer(vsl::IPlayer* _player);

		// IShip ID
		int getId();
		void setId(int _id);

		// AI Waypoints
		void addWaypoint(vsl::Vector wp);
		void removeWaypoint(int index);
		const std::vector<vsl::Vector>& getWaypoints();
		void clearWaypoints();

	protected:
		vsl::IPlayer* m_player;

	private:
		int id;
		std::vector<vsl::Vector> m_waypoints;
	};
}
