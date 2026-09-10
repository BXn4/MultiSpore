// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)

#define HOST "127.0.0.1"
#define PORT 5523

using namespace ArgScript;

class ConnectCheat : public ICommand
{
public:
	void ParseLine(const Line& line) override {
		App::ConsolePrintF("Connecting to: %s:%d", HOST, PORT);
	}
	const char* GetDescription(DescriptionMode mode) const override {
		return "Connects to: " HOST ":" STRINGIFY(PORT);
	}
};

class DisconnectCheat : public ICommand
{
public:
	void ParseLine(const Line& line) override {
	}
	const char* GetDescription(DescriptionMode mode) const override {
		return "Disconnects from the server";
	}
};

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	// these cheats temp
	CheatManager.AddCheat("connect", new ConnectCheat());
	CheatManager.AddCheat("disconnect", new DisconnectCheat());
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
