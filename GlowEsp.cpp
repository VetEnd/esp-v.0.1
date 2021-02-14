class Glow
{
public:
	void GlowEsp();
	struct GlowStruct
	{
		float r;
		float g;
		float b;
		float a;
		char m_unk[4];
		float m_flUnk;
		float m_flBloomAmount;
		float m_flUnk1;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		char m_unk1;
		int m_nFullBloomStencilTestValue;
		int m_nGlowStyle;
		int m_nSplitScreenSlot;
		int m_nNextFreeSlot;


	};
	GlowStruct EnemyGlow;
	void SetGlowStyle(int s)
	{
		EnemyGlow.m_nGlowStyle = s;
	}
	void ChangeYellowGlow()
	{
		EnemyGlow.r = 1;
		EnemyGlow.g = 1;
		EnemyGlow.b = 0;
	}
	void ChangeGreenGlow()
	{
		EnemyGlow.r = 0;
		EnemyGlow.g = 1;
		EnemyGlow.b = 0;
	}
	void ChangeRedGlow()
	{
		EnemyGlow.r = 1;
		EnemyGlow.g = 0;
		EnemyGlow.b = 0;
	}
}; extern Glow;


class Glow
{
public:
	void GlowEsp();
	struct GlowStruct
	{
		float r;
		float g;
		float b;
		float a;
		char m_unk[4];
		float m_flUnk;
		float m_flBloomAmount;
		float m_flUnk1;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		char m_unk1;
		int m_nFullBloomStencilTestValue;
		int m_nGlowStyle;
		int m_nSplitScreenSlot;
		int m_nNextFreeSlot;


	};
	GlowStruct EnemyGlow;
	void SetGlowStyle(int s)
	{
		EnemyGlow.m_nGlowStyle = s;
	}
	void ChangeYellowGlow()
	{
		EnemyGlow.r = 1;
		EnemyGlow.g = 1;
		EnemyGlow.b = 0;
	}
	void ChangeGreenGlow()
	{
		EnemyGlow.r = 0;
		EnemyGlow.g = 1;
		EnemyGlow.b = 0;
	}
	void ChangeRedGlow()
	{
		EnemyGlow.r = 1;
		EnemyGlow.g = 0;
		EnemyGlow.b = 0;
	}
}; extern Glow G;

void Glow::GlowEsp()
{
	if (CM.WantESP == 1)
	{
		DWORD Glowobject = RPM<DWORD>(Init.ClientDLL + O.dwGlowObjectManager);
		for (int i = 0; i < 20; i++)
		{
			DWORD Ent = Read.GetEntity(i);
			int GlowIndex = RPM<int>(Ent + O.m_iGlowIndex);
			if (Ent == 0) continue;
			bool dormant = RPM<int>(Ent + O.m_bDormant);
			if (dormant) continue;
			int EnTeam = RPM<int>(Ent + O.oTeam);
			EnemyGlow = RPM<GlowStruct>(Glowobject + (GlowIndex * 0x38) + 0x4);
			if (EnTeam == Read.Team)
			{
				EnemyGlow.r = 1.0f;
				EnemyGlow.g = 1.0f;
				EnemyGlow.b = 1.0f;
				EnemyGlow.a = 1.0f;
			}
			else
			{
				EnemyGlow.a = 1.0f;
				int hp = Read.GetEntityHealth(Ent);
				if (hp > 66) ChangeGreenGlow();
				else if (hp <= 66 && hp >= 33) ChangeYellowGlow();
				else ChangeRedGlow();
				if (CM.WantChams != 0) SetGlowStyle(CM.WantChams);

			}
			EnemyGlow.m_bRenderWhenOccluded = true;
			EnemyGlow.m_bRenderWhenUnoccluded = false;
			WPM<GlowStruct>(Glowobject + (GlowIndex * 0x38) + 0x4, EnemyGlow);
		}
	}
}

