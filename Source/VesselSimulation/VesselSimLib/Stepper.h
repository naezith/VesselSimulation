#ifndef STEPPER_H
#define STEPPER_H

class VESSELSIMULATION_API Stepper {
    public:
		Stepper(){}
        Stepper(float _init, float _speed);

        void step(float _dt);

        float get();
        void setSpeed(float _speed);
        float getRequested();
        void setRequested(float _requested);

        void reset(float _value);

    private:
        float m_current;
        float m_vel;
        float m_requested;
};


#endif // STEPPER_H
