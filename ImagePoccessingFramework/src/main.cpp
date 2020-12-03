
#include "entry_point.h"

struct MyApplication : Bubble::Application
{
	void OnCreate()
	{
		GetWindow().SetVSync(false);
	}

	void OnUpdate(Bubble::DeltaTime dt)
	{

	}

	void OnEvent(const SDL_Event& event)
	{

	}
};

Bubble::Application* CreateApplication()
{
	return (Bubble::Application*)new MyApplication;
}