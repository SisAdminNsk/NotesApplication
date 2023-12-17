#include "DataStorage.h"

void ProgrammState::ControlBinds::saveNewControls()
{
	this->writeFileStream.open(fileName);
	if (this->writeFileStream.is_open())
		for (const auto& bind : bindKey)
			this->writeFileStream << "command: [" << bind.first << "] |  value:{" << bind.second << "}\n";

	this->writeFileStream.close();
}

void ProgrammState::ControlBinds::loadNewControls()
{
	this->readFileStream.open(fileName);
	if (this->readFileStream.is_open()) {
		std::string reciver;
		size_t currentCommand = 0;
		while (std::getline(this->readFileStream, reciver)) {
			std::string keyCode = "";
			std::pair<size_t, size_t> beetwenIndex = std::make_pair(reciver.find("{"), reciver.find("}"));
			for (size_t i = beetwenIndex.first + 1; i < beetwenIndex.second; i++) {
				keyCode.append(std::to_string(reciver[i]));
			}
			this->bindKey[this->availableCommands.commands[currentCommand]] = keyCode;
			currentCommand++;
		}
	}
	this->readFileStream.close();
}

ProgrammState::ProgrammState() {
}

ProgrammState::SettingsBinds ProgrammState::getSettings() const
{
	return *this->settingsB;
}

std::map<std::string, std::string> ProgrammState::getControls() const
{
	return this->ctrlB->bindKey;
}


