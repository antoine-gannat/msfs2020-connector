#pragma once

class ICommand {
public:
	virtual void execute(const std::string& data) = 0;
};