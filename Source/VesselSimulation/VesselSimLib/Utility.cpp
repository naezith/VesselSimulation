#include "VesselSimulation.h"
#include "Utility.h"

FVector vsl::Utils::rotate(const FVector& loc, const FVector& eul) {
	FVector global;

	float phi = eul.X*DEG2RAD;
	float theta = eul.Y*DEG2RAD;
	float psi = eul.Z*DEG2RAD;

	global.X = +loc.X * cos(psi) * cos(theta)
		+ loc.Y * (cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi))
		+ loc.Z * (cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi));

	global.Y = +loc.X * cos(theta) * sin(psi)
		+ loc.Y * (sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi))
		+ loc.Z * (cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi));

	global.Z = -loc.X * sin(theta)
		+ loc.Y * sin(phi) * cos(theta)
		+ loc.Z * cos(phi) * cos(theta);

	return global;
}