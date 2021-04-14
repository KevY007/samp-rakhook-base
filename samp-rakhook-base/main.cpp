#include "main.h"

DWORD				g_SAMP = NULL;
HANDLE				g_DllHandle;

bool				samp037 = false;

void cmd_testhook(char* param)
{
	char	par[128];

	int ret = sscanf(param, "%s", par);
	if (ret < 1)
	{
		addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Rakhook Cmd Test");
		return;
	}
	addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "-> %s", par);
}

void ThrMainFS() 
{
	while (g_SAMP == NULL)
	{
		g_SAMP = (DWORD)GetModuleHandle("samp.dll");
		Sleep(1000);
	}
	
	bool initSampRak = false;
	while (true)
	{
		if (!initSampRak)
		{
			if (memcmp_safe((uint8_t*)g_SAMP + 0xBABE, hex_to_bin(SAMP037_CMP), 10))
			{
				samp037 = true;
			}
			else samp037 = false;

			if (samp037)
			{
				g_stSAMP037 = stGetSampInfo037();

				if (isBadPtr_writeAny(g_stSAMP037, sizeof(stSAMP_037)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP037->pPools, sizeof(stSAMPPools_037)))
				{
					continue;
				}

				g_Chat037 = stGetSampChatInfo037();
				if (isBadPtr_writeAny(g_Chat037, sizeof(stChatInfo_037)))
				{
					continue;
				}

				g_Input037 = stGetInputInfo037();
				if (isBadPtr_writeAny(g_Input037, sizeof(stInputInfo_037)))
				{
					continue;
				}

				if (g_stSAMP037->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP037->pRakClientInterface);
				g_stSAMP037->pRakClientInterface = new HookedRakClientInterface();

				SetupSAMPHook("HandleRPCPacket", SAMP037_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF5701");
				SetupSAMPHook("HandleRPCPacket2", SAMP037_HOOKENTER_HANDLE_RPC2, hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701");
				SetupSAMPHook("CNETGAMEDESTR1", SAMP037_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP037_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}
			else
			{
				g_stSAMP = stGetSampInfo();

				if (isBadPtr_writeAny(g_stSAMP, sizeof(stSAMP)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP->pPools, sizeof(stSAMPPools)))
				{
					continue;
				}

				g_Chat = stGetSampChatInfo();
				if (isBadPtr_writeAny(g_Chat, sizeof(stChatInfo)))
				{
					continue;
				}

				g_Input = stGetInputInfo();
				if (isBadPtr_writeAny(g_Input, sizeof(stInputInfo)))
				{
					continue;
				}

				if (g_stSAMP->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP->pRakClientInterface);
				g_stSAMP->pRakClientInterface = new HookedRakClientInterface();

				SetupSAMPHook("HandleRPCPacket", SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF5701");
				SetupSAMPHook("HandleRPCPacket2", SAMP_HOOKENTER_HANDLE_RPC2, hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701");
				SetupSAMPHook("CNETGAMEDESTR1", SAMP_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}

			initSampRak = true;
			addClientCommand(".rakhooktest", cmd_testhook);
			addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "{FFCC00}[SAMP-RAKHOOK-BASE] {00FF33}Loaded by KevY/0x32789 - /.rakhooktest [anything]");
		}
		if (initSampRak)
		{
			// Code if you wanna execute any. Put it in here so it doesn't execute before samp has loaded.
		}
		Sleep(100); // Adjust according to your needs
	}
}

bool OnSendRPC(int uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (uniqueID == RPCEnumeration::RPC_RequestSpawn) // Example
	{

	}
	return true;
}

bool OnSendPacket(BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	uint8_t packetId;
	parameters->ResetReadPointer();
	parameters->Read(packetId);
	
	if (packetId == PacketEnumeration::ID_BULLET_SYNC) // Example
	{

	}
	return true;
}

void HandleRPCPacketFunc(unsigned char id, RPCParameters* rpcParams, void(*callback) (RPCParameters*))
{
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
		if(id == RPC_ShowDialog) // Example
		{
			
		}
	}
	callback(rpcParams);
}

bool OnReceivePacket(Packet* p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	
	if (p->data[0] == PacketEnumeration::ID_VEHICLE_SYNC) // Example.
	{
		
	}
	return true;
}


BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, 
	DWORD fdwReason,    
	LPVOID lpReserved) 
{

	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;

	if (GetModuleHandle("samp.dll"))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThrMainFS, NULL, 0, NULL);
	}

	return TRUE;  
}