#include "VesselSimulation.h"
#include "Stepper.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"

Stepper::Stepper() : m_current(0), m_requested(0), m_vel(0) { }

void Stepper::init(float _init, float _speed) {
	m_current = m_requested = _init;
	m_vel = fabs(_speed);
}

void Stepper::step(float _dt) {
    if(m_current < m_requested) {
        m_current += m_vel*_dt;
        if(m_current > m_requested) m_current = m_requested;
    }
    else if(m_current > m_requested) {
        m_current -= m_vel*_dt;
        if(m_current < m_requested) m_current = m_requested;
    }
}

float Stepper::get() { return m_current; }

float Stepper::getRequested() { return m_requested; }

void Stepper::setRequested(float _requested) { m_requested = _requested; }

void Stepper::reset(float _value) { m_current = _value; }

void Stepper::setSpeed(float _speed) { m_vel = FMath::Abs(_speed); }
