#pragma once

#include <string>
#include "SimConnector.hpp"
#include "ICommand.hpp"
#include "Globals.hpp"

template <class T>
class ACommand: public ICommand {
public:
	ACommand(const SimConnector* connector, T step, T min, T max, const bool rollOver = false) : m_connector(connector), m_lastVal(0), m_currentVal(0), m_step(step), m_min(min), m_max(max), m_rollOver(rollOver){}
	virtual void execute(const std::string &data) = 0;

protected:
	bool updateAnalogValue(const std::string& data) {
        // if the potentio reset is set, do nothing
        if (Globals::g_potentioReset) {
            return false;
        }
        const unsigned short potentioVal = std::atoi(data.c_str());
        double newVal = this->m_currentVal;

        // if the value has barely changed, leave
        if (abs(this->m_lastVal - potentioVal) < 3) {
            return false;
        }

        // if increase
        if (potentioVal > this->m_lastVal) {
            newVal += this->m_step;
        }
        else if (potentioVal < this->m_lastVal) {
            newVal -= this->m_step;
        }

        // update the store variables
        this->m_lastVal = potentioVal;
        if (newVal > this->m_max) {
            this->m_currentVal = this->m_rollOver ? this->m_min : this->m_max;
        }
        else if (newVal < this->m_min) {
            this->m_currentVal = this->m_rollOver ? this->m_max : this->m_min;
        }
        else {
            this->m_currentVal = newVal;
        }
        return true;
	}

    bool updateDigitalValue(const std::string& data) {
        const int value = std::atoi(data.c_str());
        if (value == (int)this->m_lastVal) {
            return false;
        }
        this->m_lastVal = value;
        this->m_currentVal = value;
        return true;
    }

	const SimConnector *m_connector;
	T m_step;
	T m_lastVal;
	T m_currentVal;
    T m_min;
    T m_max;
    bool m_rollOver;
};