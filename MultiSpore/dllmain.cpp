// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

/*#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define HOST "127.0.0.1"
#define PORT 5523

SOCKET sock = INVALID_SOCKET;
sockaddr_in socketAddress{}; */

using namespace ArgScript;

struct Position {
	float x, y, z;
};

Vector3 GetPos();


class GetPositionCheat
	: public ICommand
{
public:
	void ParseLine(const Line& line) override {
		Vector3 position = GetPos();
		App::ConsolePrintF("Player position: %f, %f", position.x, position.y, position.z);
	}
	const char* GetDescription(DescriptionMode mode) const override {
		return "TEST COMMAND: Gets the player position";
	}
};

Vector3 GetPos()
{
	// X+Y pos for the cell game mode
	// X+Y+Z for other game modes
    Vector3 position{};

    switch (GameModeManager.GetActiveModeID()) {
    case kGameCell: {
        Simulator::Cell::cCellObjectData* playerCell = Simulator::Cell::GetPlayerCell();

        if (!playerCell)
        {
            App::ConsolePrintF("COULD NOT FIND PLAYER CELL");
			break;
        } else {
            position = playerCell->GetPosition();
        }

        break;
    }

	case kGameCreature: {
		break;
	}

    case kGameTribe:
        break;

    case kGameCiv:
        break;

    case kGameSpace:
        break;

    default:
        App::ConsolePrintF("UNKNOWN GAME MODE");
        break;
    }

    return position;
}

/* void SendClientPosition(const Vector3& position)
{
	Position packet{
		position.x,
		position.y,
		position.z
	};

	sendto(
		sock,
		reinterpret_cast<const char*>(&packet),
		sizeof(packet),
		0,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress)
	);
} */

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	/*WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		socketAddress.sin_family = AF_INET;
		socketAddress.sin_port = htons(PORT);
		inet_pton(AF_INET, HOST, &socketAddress.sin_addr);
	}*/

	CheatManager.AddCheat("getpos", new GetPositionCheat());
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
BOOL APIENTRY DllMain( HMODULE hModule,
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
