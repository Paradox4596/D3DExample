#include "Input.h"

namespace MyUtil
{
	void Input::Initialize()
	{
		mKeys.fill(false);
		mCursorX = mCursorY = 0;
	}
	void Input::SetKeyDown(unsigned int key)
	{
		mKeys[key]
	}
	void Input::SetKeyUp(unsigned int key)
	{
	}
	void Input::SetCursor(int x, int y)
	{
	}
	bool Input::IsKeyDown(unsigned int key)
	{
		return false;
	}
	void Input::GetCursor(int& x, int& y)
	{
	}
}