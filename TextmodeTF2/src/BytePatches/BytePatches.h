#include "../SDK/SDK.h"
#include "../Utils/Feature/Feature.h"

class BytePatch
{
	const char* m_sModule = nullptr;
	const char* m_sSignature = nullptr;
	int m_iOffset = 0x0;
	std::vector<byte> m_vPatch = {};
	std::vector<byte> m_vOriginal = {};
	size_t m_iSize = 0;
	LPVOID m_pAddress = 0;
	bool m_bIsPatched = false;

	void Write(std::vector<byte>& bytes);

public:
	BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch);

	bool Initialize();
	void Unload();
};

class CBytePatches
{
public:
	bool Initialize(const char* cModule);
	void Unload();

	std::unordered_map<const char*, std::vector<BytePatch>> m_mPatches =
	{
		{"engine",
		{
			// V_RenderView
			// Removes Sleep(15) call
			BytePatch("engine.dll", "E8 ? ? ? ? 48 85 FF 74 ? 45 33 C9 89 74 24", 0x0, "90 90 90 90 90"),
			// Skip downloading resources
			BytePatch("engine.dll", "75 ? 48 8B 0D ? ? ? ? 48 8D 93", 0x0, "71"),
			// The method
			BytePatch("engine.dll", "0F 85 ? ? ? ? 48 8D 15 ? ? ? ? B9", 0x0, "0F 81")
		}},
		{"client",
		{
			// C_BaseAnimating::DoAnimationEvents
			BytePatch("client.dll", "0F 84 ? ? ? ? 53 41 56 48 83 EC ? 83 B9", 0x0, "C3"),
			// CParticleCollection::Init
			BytePatch("client.dll", "57 48 83 EC ? 48 8B DA 48 8B F9 48 85 D2 74 ? 48 8B 0D ? ? ? ? 48 8B 89", 0x0, "31 C0 90 90 C3"),
			// CParticleSystemMgr::PrecacheParticleSystem
			BytePatch("client.dll", "74 ? 53 48 83 EC ? 80 3A", 0x0, "C3"),
			// CParticleProperty::Create
			// no longer breaks amalgam since i made a textmode version of it
			BytePatch("client.dll", "44 89 44 24 ? 53 55 56 57 41 54 41 56", 0x0, "31 C0 C3"),
			// CViewRender::Render
			BytePatch("client.dll", "48 89 50 ? 55 57 41 56", 0x0, "31 C0 C3"),
			// This fixes the datacache.dll crash
			BytePatch("client.dll", "4D 85 F6 0F 84 ? ? ? ? 49 8B CE E8 ? ? ? ? 83 F8", 0x0, "83 F6 00"),

			// CCharacterInfoPanel::CCharacterInfoPanel (Prevent panel initializations)
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 41 B8 ? ? ? ? 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B C8 EB ? 48 8B CD 48 89 8E ? ? ? ? 48 8B D6 48 8B 01 FF 90 ? ? ? ? 48 8B 96 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B CE E8 ? ? ? ? B9", 0x0, "E9 B9 00"),
			BytePatch("client.dll", "48 8B 8E ? ? ? ? 33 D2 48 8B 01 FF 90 ? ? ? ? 4C 8D 5C 24", 0x0, "EB 15"),

			// CCharacterInfoPanel::CreateStorePanel (Do nothing)
			BytePatch("client.dll", "48 83 EC ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 48 8B 10 FF 92 ? ? ? ? E8", 0x0, "5B C3 CC"),

			// CCharacterInfoPanel::Close (Prevent m_pLoadoutPanel call)
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 8D 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? 4C 8B C0 EB ? 45 33 C0 48 8B 03 0F 57 DB 48 8B 93 ? ? ? ? 48 8B CB FF 90 ? ? ? ? 48 8B 0D", 0x0, "EB 3A"),
		
			// CCharacterInfoPanel::OnCommand (Prevent m_pLoadoutPanel calls)
			BytePatch("client.dll", "48 8D 15 ? ? ? ? 48 3B FA 74 ? 48 8B CF E8 ? ? ? ? 85 C0 74 ? 48 8B 0D ? ? ? ? 48 8B D7 48 8B 01 FF 50 ? E9", 0x0, "EB 16"),
	
			// CCharacterInfoPanel::OpenEconUI (Prevent m_pLoadoutPanel calls)
			BytePatch("client.dll", "48 8D B1 ? ? ? ? 48 8B D9 48 8B 06", 0x1, "8B C1 48 83 C4 20 41 5E C3"),

			// CCharacterInfoPanel::ShowPanel (Prevent m_pLoadoutPanel calls)
			BytePatch("client.dll", "0F 84 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B C8", 0x2, "59"),
			BytePatch("client.dll", "0F 84 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B C8", 0x6, "E9 E2 00 00 00"),
			BytePatch("client.dll", "49 8B 8E ? ? ? ? 45 33 C0 8B 91", 0x0, "EB 64"),
			BytePatch("client.dll", "49 8B 06 49 8B CE FF 90 ? ? ? ? 84 C0 74 ? 49 8B 8E", 0x0, "E9 EA 00 00 00"),

			// CCharacterInfoPanel::IsUIPanelVisible (Prevent m_pLoadoutPanel calls)
			BytePatch("client.dll", "74 ? 83 EB ? 74 ? 83 EB ? 74 ? 83 FB ? 75 ? 48 8B 47", 0x0, "EB"),

			// CTFPlayerInventory::SOUpdated (Prevent CCharacterInfoPanel::GetBackpackPanel call)
			BytePatch("client.dll", "75 ? E8 ? ? ? ? 48 8B C8 48 8B 10 FF 52 ? 48 8B 53", 0x0, "EB"),
		}}
	};
};

ADD_FEATURE_CUSTOM(CBytePatches, BytePatches, U);