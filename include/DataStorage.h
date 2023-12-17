#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

class ProgrammState {
public:
	const enum class gameStates { isGameLoop, isMenu, isMenuControlButton, isMenuPlayButton, isSettingsButton };
	const enum class inlineGameStates { DefaultState = 0, isGameLoopMenu };
	const enum class actionGameStates {DefaultState = 0, isSolveLabirintSimulation};

	gameStates currentState = gameStates::isMenu;
	inlineGameStates currentInlineState = inlineGameStates::DefaultState;
	actionGameStates currentActionState = actionGameStates::DefaultState;

	struct SettingsBinds {

		SettingsBinds() {};
	};

	struct ControlBinds {
	private:
		struct Commands {
			const std::vector<std::string> commands = { "camera left","camera right","camera up",
			"camera down","reset camera","back to menu","show game menu","generate labirint" };
		};

		std::ofstream writeFileStream;
		std::ifstream readFileStream;

	public:
		const Commands availableCommands;

		// control's that can be changed
		std::map<std::string, std::string> bindKey = { {availableCommands.commands[0],"A"},{availableCommands.commands[1],"D"},
			{availableCommands.commands[2],"W"} ,{availableCommands.commands[3],"S"}, {availableCommands.commands[4], "SPACE"},
			{availableCommands.commands[5],"M"},{availableCommands.commands[6],"TAB"}, {availableCommands.commands[7],"->"}
		};

		const std::string fileName = "controls.txt";

		void saveNewControls();
		void loadNewControls();// set new bindKey value's
	};

public:
	ProgrammState(ControlBinds* ctrlB_, SettingsBinds* settingsB_) : ctrlB(ctrlB_), settingsB(settingsB_) {}
	ProgrammState();

	SettingsBinds  getSettings() const;
	std::map<std::string, std::string> getControls() const;

private:
	ControlBinds* ctrlB;
	SettingsBinds* settingsB;
};