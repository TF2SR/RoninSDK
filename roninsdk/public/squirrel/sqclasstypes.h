#pragma once
#include "sqdatatypes.h"


enum SQRESULT : SQInteger
{
	SQRESULT_ERROR = -1,
	SQRESULT_NULL = 0,
	SQRESULT_NOTNULL = 1,
};

typedef SQRESULT(*SQFunction)(HSquirrelVM* sqvm);

enum class eSQReturnType
{
	Float = 0x1,
	Vector = 0x3,
	Integer = 0x5,
	Boolean = 0x6,
	Entity = 0xD,
	String = 0x21,
	Default = 0x20,
	Arrays = 0x25,
	Asset = 0x28,
	Table = 0x26,
};

enum class ScriptContext : int
{
	INVALID = -1,
	SERVER,
	CLIENT,
	UI,
};

struct SQBufferState
{
	const SQChar* buffer;
	const SQChar* bufferPlusLength;
	const SQChar* bufferAgain;

	SQBufferState(const std::string& code)
	{
		buffer = code.c_str();
		bufferPlusLength = code.c_str() + code.size();
		bufferAgain = code.c_str();
	}
};

struct SQFuncRegistration
{
	const char* squirrelFuncName;
	const char* cppFuncName;
	const char* helpText;
	const char* returnTypeString;
	const char* argTypes;
	uint32_t unknown1;
	uint32_t devLevel;
	const char* shortNameMaybe;
	uint32_t unknown2;
	eSQReturnType returnType;
	uint32_t* externalBufferPointer;
	uint64_t externalBufferSize;
	uint64_t unknown3;
	uint64_t unknown4;
	void* funcPtr;

	SQFuncRegistration()
	{
		memset(this, 0, sizeof(SQFuncRegistration));
		this->returnType = eSQReturnType::Default;
	}
};