// CORE.Keyboard.h
//////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
// Keyboard
static class Keyboard {
public:
	static bool W;
	static bool A;
	static bool S;
	static bool D;
	static bool UpArrow;
	static bool LeftArrow;
	static bool RightArrow;
	static bool DownArrow;

	Keyboard::Keyboard();

	static void RunKeyboardKeys();

};