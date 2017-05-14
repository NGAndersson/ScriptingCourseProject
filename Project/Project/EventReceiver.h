#pragma once
#include <irrlicht.h>

using namespace irr;

//Keeps track of the states of all keyboard keys
class EventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	EventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
