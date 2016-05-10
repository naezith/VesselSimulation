#include "VesselSimulation.h"
#include "Stepper.h"
#include <cmath>

vsl::Stepper::Stepper() : m_current(0), m_requested(0), m_vel(0) { }

void vsl::Stepper::init(float _init, float _speed) {
	m_current = m_requested = _init;
	m_vel = fabs(_speed);
}

void vsl::Stepper::step(float _dt) {
    if(m_current < m_requested) {
        m_current += m_vel*_dt;
        if(m_current > m_requested) m_current = m_requested;
    }
    else if(m_current > m_requested) {
        m_current -= m_vel*_dt;
        if(m_current < m_requested) m_current = m_requested;
    }
}

float vsl::Stepper::get() { return m_current; }

float vsl::Stepper::getRequested() { return m_requested; }

void vsl::Stepper::setRequested(float _requested) { m_requested = _requested; }

void vsl::Stepper::reset(float _value) { m_current = _value; }

void vsl::Stepper::setSpeed(float _speed) { m_vel = std::abs(_speed); }
