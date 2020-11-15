#pragma once
#include <gl/freeglut.h>
#include <unordered_map>

class KeyBoard final
{
private:
	static constexpr auto Key_Max = 256;
	static bool mKeys[Key_Max];
	static bool mFirsts[Key_Max];
	static std::unordered_map<int, bool> mSpecialKeys;

public:
	KeyBoard();
	~KeyBoard() noexcept;

	void initalize();

	void update();

	bool isKeyPressed(unsigned char key) const { return (static_cast<int>(key) >= Key_Max) ? false : mKeys[static_cast<int>(key)]; }
	bool isKeyFirst(unsigned char key) const { return (static_cast<int>(key) >= Key_Max) ? false : mFirsts[static_cast<int>(key)]; }
	bool isSpecialKeyPressed(int key) const { return mSpecialKeys[key]; }

private:
	friend GLvoid keyDownCallBack(unsigned char key, int x, int y);
	friend GLvoid keyUpCallBack(unsigned char key, int x, int y);
	friend GLvoid specialKeyDownCallBack(int key, int x, int y);
	friend GLvoid specialKeyUpCallBack(int key, int x, int y);
};

