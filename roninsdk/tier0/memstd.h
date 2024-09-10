#ifndef MEMSTD_H
#define MEMSTD_H

// From northstar
/*
0 void* unknown[1]; // alloc debug
1 void* (*Alloc)(IMemAlloc* memAlloc, size_t nSize);
2 void* unknown2[1]; // realloc debug
3 void* (*Realloc)(IMemAlloc* memAlloc, void* pMem, size_t nSize);
4 void* unknown3[1]; // free #1
5 void (*Free)(IMemAlloc* memAlloc, void* pMem);
6 void* unknown4[2]; // nullsubs, maybe CrtSetDbgFlag
8 size_t (*GetSize)(IMemAlloc* memAlloc, void* pMem);
9 void* unknown5[9]; // they all do literally nothing
18 void (*DumpStats)(IMemAlloc* memAlloc);
19 void (*DumpStatsFileBase)(IMemAlloc* memAlloc, const char* pchFileBase);
23 void* unknown6[4];
24 int (*heapchk)(IMemAlloc* memAlloc);

??_7CStdMemAlloc@@6B@
				 dq offset sub_180013910
                 dq offset sub_180013780
                 dq offset sub_180016080
                 dq offset sub_180015F50
                 dq offset sub_180014EC0
                 dq offset sub_180014DF0
                 dq offset sub_180014B60
                 dq offset sub_180014B50
                 dq offset sub_180015370
                 dq offset nullsub_3
                 dq offset nullsub_4
                 dq offset sub_1800146F0
                 dq offset sub_180014730
                 dq offset sub_1800146C0
                 dq offset sub_1800146D0
                 dq offset sub_1800146A0
                 dq offset sub_180014700
                 dq offset nullsub_5
                 dq offset sub_180014A30
                 dq offset sub_180014A50
                 dq offset sub_1800143E0
                 dq offset sub_180014FF0
                 dq offset sub_180014710
                 dq offset sub_180014720
                 dq offset sub_1800146B0
                 dq offset sub_180017730
                 dq offset sub_180015A00
                 dq offset nullsub_6
                 dq offset nullsub_7
                 dq offset nullsub_8
                 dq offset sub_180015430
                 dq offset sub_180014260
                 dq offset sub_180016C10
                 dq offset nullsub_9
                 dq offset nullsub_10
                 dq offset sub_180015BF0
                 dq offset sub_180014360
                 dq offset sub_180015C00
                 dq offset sub_180016350
                 dq offset sub_1800161B0
                 dq offset sub_1800154B0
                 dq offset sub_180013AE0
                 dq offset sub_180015000
                 dq offset sub_180013110
*/

class IMemAlloc
{
public:
	template<typename T>
	T* Alloc(size_t nSize)
	{
		const static int index = 1;
		return CallVFunc<T*>(index, this, nSize);
	}
	template<typename T>
	T* Realloc(T* pMem, size_t nSize)
	{
		const static int index = 3;
		return CallVFunc<T*>(index, this, pMem, nSize);
	}
	template<typename T>
	void Free(T* pMem)
	{
		const static int index = 5;
		CallVFunc<void>(index, this, pMem);
	}
	template<typename T>
	size_t GetSize(T* pMem)
	{
		const static int index = 8;
		return CallVFunc<size_t>(index, this, pMem);
	}
};

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
class CStdMemAlloc : public IMemAlloc {};

inline CMemory p_CreateGlobalMemAlloc;
inline auto v_CreateGlobalMemAlloc = p_CreateGlobalMemAlloc.RCast<CStdMemAlloc* (*)(void)>();

inline CStdMemAlloc* g_pMemAllocSingleton = nullptr;


inline CStdMemAlloc* MemAllocSingleton()
{
	if (!g_pMemAllocSingleton)
	{
		g_pMemAllocSingleton = v_CreateGlobalMemAlloc();
	}
	return g_pMemAllocSingleton;
}

///////////////////////////////////////////////////////////////////////////////
class VMemStd : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CreateGlobalMemAlloc", p_CreateGlobalMemAlloc.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CreateGlobalMemAlloc = g_pTier0Dll->GetExportedFunction("CreateGlobalMemAlloc");
		v_CreateGlobalMemAlloc = p_CreateGlobalMemAlloc.RCast<CStdMemAlloc* (*)(void)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////

#endif // MEMSTD_H
