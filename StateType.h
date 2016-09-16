#ifndef STATE_TYPE_H
#define STATE_TYPE_H

//Because multiple classes will be using this. 
//Its best to have this enumeration as its own file

enum class StateType
{
	Base,
	MainMenu, 
	Paused,
	Game,
	WinScreen,
	DeathScreen,
	EndGame
};
#endif // !STATE_TYPE_H
