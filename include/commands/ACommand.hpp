#pragma once

#include <string>
#include "SimConnector.hpp"
#include "ICommand.hpp"

template <class T>
class ACommand: public ICommand {
public:
	ACommand(const SimConnector* connector, T step) : m_connector(connector), m_lastVal(0), m_currentVal(0), m_step(step){}
	virtual void execute(const std::string &data) = 0;

protected:
	bool updateAnalogValue(const std::string& data) {
        const unsigned short potentioVal = std::atoi(data.c_str());
        double newVal = this->m_currentVal;

        // if the value has barely changed, leave
        if (abs(this->m_lastVal - potentioVal) < 3) {
            return false;
        }

        // if increase
        const double diff = abs(this->m_lastVal - potentioVal);
        if (potentioVal > this->m_lastVal) {
            newVal += (diff * this->m_step);
        }
        else if (potentioVal < this->m_lastVal) {
            newVal -= (diff * this->m_step);
        }

        // update the store variables
        this->m_lastVal = potentioVal;
        this->m_currentVal = newVal;
        return true;
	}

    bool updateDigitalValue(const std::string& data) {
        const unsigned short value = std::atoi(data.c_str());
        if (value == (unsigned short)this->m_lastVal) {
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
};