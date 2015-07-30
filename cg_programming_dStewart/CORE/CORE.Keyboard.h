// CORE.Keyboard.h
//////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
// Keyboard
class Keyboard {
public:
	static bool Escape;
	static bool W;
	static bool A;
	static bool S;
	static bool D;
	static bool Q;
	static bool E;
	static bool UpArrow;
	static bool LeftArrow;
	static bool RightArrow;
	static bool DownArrow;
	

	Keyboard::Keyboard();

	static void RunKeyboardKeys();

};