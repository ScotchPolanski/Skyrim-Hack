#include "Functions.h"

int ix;
DWORD EntityObjStart = 0x0;
DWORD EntlistJmpBack = 0x0;
DWORD noclipJmpBack = 0x0;
DWORD Axis = 0x0;
DWORD zAxisptr = 0x0;
bool alreadyThere = false;

class playerent;
class nameptrClass;
class boneptr1Class;
class boneptr2Class;
class boneprt3Class;

class playerent
{
public: 
	char pad_0x0000[0x24]; //0x0000
	nameptrClass* nameptr; //0x0024
	char pad_0x0028[0xC]; //0x0028
	vec3 coords; //0x0034
	char pad_0x0040[0x148]; //0x0040
	boneptr1Class* boneptr1;
	char pad_0x018C[0x2B4];
}; // Size=0x0440

class nameptrClass
{
public:
	char pad_0x0000[0x88]; //0x0000
	char* name; //0x0088
	char pad_0x008C[0x378]; //0x008C
}; //Size=0x0404



// BONES

class boneptr1Class
{
public:
	char pad_0x0000[0x4];
	boneptr2Class* boneptr2;
	char pad_0x0008[0x3FC];
};

class boneptr2Class
{
public:
	char pad_0x0000[0xC0];
	boneprt3Class* boneptr3;
	char pad_0x00C4[0x340];
};

class boneprt3Class
{
public:
	char pad_0x0000[0x74];
	char* humanoidvalidation;
	char pad_0x0078[0x58];
	vec3 b1;
	char pad_0x00DC[0x6C];
	vec3 b2;
	char pad_0x0154[0x6C];
	vec3 b3;
	char pad_0x01CC[0x6C];
	vec3 b4;
	char pad_0x0244[0x6C];
	vec3 b5;
	char pad_0x02BC[0x6C];
	vec3 b6;
	char pad_0x0334[0x6C];
	vec3 b7;
	char pad_0x03AC[0x6C];
	vec3 b8;
	char pad_0x0424[0x6C];
	vec3 b9;
	char pad_0x049C[0x24C];
	vec3 b10;
	char pad_0x06F4[0x6C];
	vec3 b11;
	char pad_0x076C[0x6C];
	vec3 b12;
	char pad_0x07E4[0x6C];
	vec3 b13;
	char pad_0x085C[0x6C];
	vec3 b14;
	char pad_0x08D4[0x6C];
	vec3 b15;
	char pad_0x094C[0x6C];
	vec3 b16;
	char pad_0x09C4[0x6C];
	vec3 b17;
	char pad_0x0A3C[0x6C];
	vec3 b18;
	char pad_0x0AB4[0x6C];
	vec3 b19;
	char pad_0x0B2C[0x6C];
	vec3 b20;
	char pad_0x0BA4[0x6C];
	vec3 b21;
	char pad_0x0C1C[0x6C];
	vec3 b22;
	char pad_0x0C94[0x6C];
	vec3 b23;
	char pad_0x0D0C[0x6C];
	vec3 b24;
	char pad_0x0D84[0x6C];
	vec3 b25;
	char pad_0x0DFC[0x6C];
	vec3 b26;
	char pad_0x0E74[0x6C];
	vec3 b27;
	char pad_0x0EEC[0x6C];
	vec3 b28;
	char pad_0x0F64[0x6C];
	vec3 b29;
	char pad_0x0FDC[0x6C];
	vec3 b30;
	char pad_0x1054[0x6C];
	vec3 b31;
	char pad_0x10CC[0x6C];
	vec3 b32;
	char pad_0x1144[0x774];
	vec3 b33;
	char pad_0x18C4[0x6C];
	vec3 b34;
	char pad_0x1A2C[0x6C];
	vec3 b35;
	char pad_0x1AA4[0x6C];
	vec3 b36;
	char pad_0x1B1C[0x6C];
	vec3 b37;
	char pad_0x1B94[0x6C];
	vec3 b38;
	char pad_0x1C0C[0x6C];
	vec3 b39;
	char pad_0x1C84[0x6C];
	vec3 b40;
	char pad_0x1CFC[0x6C];
	vec3 b41;
	char pad_0x1D74[0x6C];
	vec3 b42;
	char pad_0x1DEC[0x774];
	vec3 b43;
	char pad_0x256C[0x6C];
	vec3 b44;
	char pad_0x26D4[0x6C];
	vec3 b45;
	char pad_0x274C[0x6C];
	vec3 b46;
	char pad_0x27C4[0x6C];
	vec3 b47;
	char pad_0x283C[0x6C];
	vec3 b48;
	char pad_0x28B4[0x750];
};

playerent * ents[255];
playerent * entsptr;


__declspec(naked) void entityhook()
{
	__asm {
		mov edx, [esi + 0x34]
		mov eax, [esi + 0x38]
		mov EntityObjStart, esi
		pushad
	}

	__asm {
		mov eax, EntityObjStart
		mov[entsptr], eax
	}

	if (entsptr == nullptr)
	{
		goto GIVE_UP;
	}

	alreadyThere = false;

	for (ix = 0; ix < 254; ix++)
	{
		if (ents[ix] == entsptr)
		{
			alreadyThere = true;
			break;
		}
	}

	if (alreadyThere)
	{
		goto GIVE_UP;
	}
	else
	{
		for (ix = 0; ix < 254; ix++)
		{
			if (ents[ix] == 0)
			{
				ents[ix] = entsptr;
				break;
			}
		}
	}

GIVE_UP:
	__asm {
		popad
		jmp[EntlistJmpBack]
	}
}

__declspec(naked) void nocliphook()
{
	__asm {
		mov zAxisptr, esi
		mov edx, [edx + 0x78]
		fld dword ptr[edx + 0x0C]
		pushad
	}

	__asm {
		popad
		jmp[noclipJmpBack]
	}
}