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
			BytePatch("engine.dll", "0F 85 ? ? ? ? 48 8D 15 ? ? ? ? B9", 0x0, "0F 81"),
			// Force Con_DebugLog to run
			BytePatch("engine.dll", "74 ? 48 8D 54 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 38 1D", 0x0, "90 90"),

			// evil cathook's plan b implementation

			// Mod_LoadLighting
			// nulls out lighting data loading for maps
			BytePatch("engine.dll", "40 53 48 83 EC 20 48 8B D9 48 63 09 85 C9 75 18", 0x0, "C3"),
			
			// Sprite_LoadModel
			// nulls out sprite model loading
			BytePatch("engine.dll", "48 89 5C 24 08 48 89 74 24 18 57 41 56 41 57 48", 0x0, "C3"),

			// Mod_LoadWorldlights
			// nulls out world light loading
			BytePatch("engine.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57", 0x0, "C3"),

			// Mod_LoadTexinfo
			// forces mat_loadtextures 0 logic to skip material loading
			BytePatch("engine.dll", "0F 84 ? ? ? ? 48 63 7E 44", 0x0, "90 E9"),
			
			// These SHOULD fix d3device failure
			// CVideoMode_Common::CreateGameWindow
			BytePatch("engine.dll", "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 83 EC 50 4C 8B F1 41 0F B6 F1 48 8D 0D ? ? ? ?", 0x0, "B0 01 C3"),
			// CGame::CreateGameWindow
			BytePatch("engine.dll", "40 55 53 56 57 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F1 C6 45 D0 00 B9 40 00", 0x0, "B0 01 C3"),
		}},
		{"materialsystem",
		{
			// CMaterialSystem::Init
			// Returns 1 (INIT_OK) to prevent material system initialization but allow engine to continue anywyay
			BytePatch("materialsystem.dll", "40 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B 0D", 0x0, "B8 01 00 00 00 C3"),

			// CMaterialSystem::BeginFrame
			// bye bye frame rendering!
			BytePatch("materialsystem.dll", "48 8B 0D ? ? ? ? 48 8B 01 48 FF A0 ? ? ? ? CC", 0x0, "C3"),

			// CMaterialSystem::FindMaterial
			// returns NULL for every material lookup
			// BytePatch("materialsystem.dll", "48 8B F9 48 8B CA 49 8B D8 FF 10 4C 8B C0 48 8D 15 ? ? ? ? 48 8D 4C 24 20", 0x0, "31 C0 C3"),
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
			BytePatch("client.dll", "44 89 44 24 ? 53 55 56 57 41 54 41 56", 0x0, "31 C0 C3"),
			// CViewRender::Render
			BytePatch("client.dll", "48 89 50 ? 55 57 41 56", 0x0, "31 C0 C3"),

			// This fixes the datacache.dll crash
			BytePatch("client.dll", "4D 85 F6 0F 84 ? ? ? ? 49 8B CE E8 ? ? ? ? 83 F8", 0x0, "83 F6 00"),

			// CCharacterInfoPanel::CCharacterInfoPanel (Prevent panel initializations)
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 41 B8 ? ? ? ? 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B C8 EB ? 48 8B CD 48 89 8E ? ? ? ? 48 8B D6 48 8B 01 FF 90 ? ? ? ? 48 8B 96 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B CE E8 ? ? ? ? B9", 0x0, "E9 B9 00"),
			BytePatch("client.dll", "48 8B 8E ? ? ? ? 33 D2 48 8B 01 FF 90 ? ? ? ? 4C 8D 5C 24", 0x0, "EB 10"),	

			// CStorePanel::RequestPricesheet (avoids calling CCharacterInfoPanel::CreateStorePanel and CGCClientJobGetUserData)
			BytePatch("client.dll", "40 57 48 83 EC ? E8 ? ? ? ? 48 8B C8", 0x0, "C3"),

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

			// Create_CTFWinPanel
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 33 D2 41 B8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 33 FF 48 85 DB 74 ? 44 8D 47 ? 48 8B CB 48 8D 15 ? ? ? ? E8 ? ? ? ? 48 8B C8 EB ? 48 8B CF 48 8B 5C 24 ? 48 8D 81 ? ? ? ? 48 85 C9 48 0F 44 C7 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 54 24", 0x0, "48 B8 00 00 00 00 00 00 00 00 48 83 C4 20 5F C3"),

			// Create_CTFHudDeathNotice
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 33 D2 41 B8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 85 DB 74 ? 41 B8 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B CB 48 83 C4 ? 5B E9 ? ? ? ? 33 C0 48 83 C4 ? 5B C3 CC CC CC CC CC CC 40 53 48 83 EC ? B9 ? ? ? ? E8 ? ? ? ? 33 D2 41 B8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 85 DB 74 ? 41 B8 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B CB 48 83 C4 ? 5B E9 ? ? ? ? 33 C0 48 83 C4 ? 5B C3 CC CC CC CC CC CC 48 8D 0D", 0x0, "EB 3A"),

			// Create_CTFFreezePanel
			BytePatch("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 33 D2 41 B8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 33 FF 48 85 DB 74 ? 44 8D 47 ? 48 8B CB 48 8D 15 ? ? ? ? E8 ? ? ? ? 48 8B C8 EB ? 48 8B CF 48 8B 5C 24 ? 48 8D 81 ? ? ? ? 48 85 C9 48 0F 44 C7 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? B9", 0x0, "48 B8 00 00 00 00 00 00 00 00 48 83 C4 20 5F C3"),

			// CBaseHudChat::ChatPrintf
			BytePatch("client.dll", "4C 89 4C 24 ? 48 89 4C 24 ? 55 53", 0x0, "C3"),

			// Fixes crash (CEconItemView::GetItemDefinitionIndex)
			BytePatch("client.dll", "48 8B 41 08 48 85 C0 75 0A 48 8B 01 8B 80 BC 00 00 00 C3 8B 40 20 C3", 0x0, "48 8B 41 08 48 85 C0 75 0F 48 8B 01 48 85 C0 74 0B 8B 80 BC 00 00 00 C3 8B 40 20 C3 31 C0 C3"),
			
			// Fixes crash
			BytePatch("client.dll", "45 85 C0 78 3E 4C 8B 11 45 3B 82 E8 00 00 00 7D 32", 0x0, "4C 8B 11 4D 85 D2 74 3B 45 3B 82 E8 00 00 00 73 32"),
		}},
		{"datacache",
		{
			// CDataCacheSection::Unlock CRASHFIX!
			BytePatch("datacache.dll", "48 89 5C 24 18 48 89 7C 24 20 41 56 48 83 EC 20 F6 81 E0 00 00 00 04", 0x41, "90 90 90 90 90"),
		}},
		{"studiorender",
		{
			// CStudioRender::DrawModelArray
			BytePatch("studiorender.dll", "40 53 48 83 EC 20 48 8D 05 ? ? ? ? 48 8B D9", 0x0, "C3"),

			// CStudioRenderContext::AddShadows
			BytePatch("studiorender.dll", "40 53 56 57 41 55 41 57 48 83 EC 30 48 8B 0D ? ? ? ?", 0x0, "C3"),

			// CStudioRenderContext (model rendering setup)
			BytePatch("studiorender.dll", "4C 89 4C 24 20 48 89 4C 24 08 56 41 54 41 55 41 56 41 57 48 83 EC 70", 0x0, "C3"),

			// CStudioRenderContext (another model rendering path)
			BytePatch("studiorender.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 44 89 4C 24 20 57 41 56 41 57 48 83 EC 40", 0x0, "C3"),

			// Disables bone setup only needed for drawing
			BytePatch("studiorender.dll", "4C 89 44 24 18 48 89 54 24 10 48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 81 EC D0 00 00", 0x0, "31 C0 C3"),
		}},
		{"vguimatsurface",
		{
			// PaintTraverse
			BytePatch("vguimatsurface.dll", "40 57 48 83 EC 30 80 A1 ? ? ? ? 9F 48 8B F9", 0x0, "C3"),

			// DrawPrintText
			BytePatch("vguimatsurface.dll", "44 89 4C 24 20 48 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 81 EC C0 00 00 00", 0x0, "C3"),

			// AddGlyphToCache
          	BytePatch("vguimatsurface.dll", "4C 89 4C 24 20 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 81 EC E0 00 00 00", 0x0, "31 C0 C3"),

          	// FlushText
          	BytePatch("vguimatsurface.dll", "40 53 48 83 EC 30 83 B9 A8 03 01 00 00 48 8B D9", 0x0, "C3"),
        }},
		// if something will start to crash i blame this at the first
		{"shaderapidx9",
		{
			// Present
			BytePatch("shaderapidx9.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57", 0x0, "C3"),

			// CreateTextures
			BytePatch("shaderapidx9.dll", "44 89 4C 24 20 44 89 44 24 18 48 89 54 24 10 55", 0x0, "31 C0 C3"),

			// ModifyTexture
			BytePatch("shaderapidx9.dll", "4C 8B DC 49 89 5B 10 57 48 83 EC 50 48 8B 05", 0x0, "C3"),

			// CreateTextureHandles
			BytePatch("shaderapidx9.dll", "4C 8B DC 56 41 55 48 81 EC 98 00 00 00 48 8B 05", 0x0, "C3"),

			// TexLock
			BytePatch("shaderapidx9.dll", "4C 8B DC 49 89 5B 10 49 89 6B 18 56 57 41 54 41", 0x0, "31 C0 C3"),

			// TexUnlock
			BytePatch("shaderapidx9.dll", "4C 8B DC 49 89 5B 10 49 89 73 18 57 48 83 EC 50", 0x0, "C3"),

			// CrashFix
			BytePatch("shaderapidx9.dll", "40 53 55 57 41 56 41 57 48 83 EC 50 48 8B 81", 0x0, "C3"),
		}},
	};
};

ADD_FEATURE_CUSTOM(CBytePatches, BytePatches, U);
