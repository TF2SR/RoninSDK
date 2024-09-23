#include "squirrel/squirrelmanager.h"
#include "nlohmann/json.hpp"

namespace SHARED
{
	template <ScriptContext context> void EncodeJsonArray(
		SQArray* arr,
		nlohmann::json obj)
	{
		for (int i = 0; i < arr->_usedSlots; i++)
		{
			SQObject* node = &arr->_values[i];

			nlohmann::json newObj;
			nlohmann::json newArray = nlohmann::json::array();

			switch (node->_Type)
			{
			case OT_STRING:
				obj.push_back(reinterpret_cast<const char*>(node->_VAL.asString->_val));
				break;
			case OT_INTEGER:
				obj.push_back(node->_VAL.asInteger);
				break;
			case OT_FLOAT:
				obj.push_back(node->_VAL.asFloat);
				break;
			case OT_BOOL:
				if (node->_VAL.asInteger)
					obj.push_back(true);
				else
					obj.push_back(false);
				break;
			case OT_TABLE:
				EncodeJsonTable<context>(node->_VAL.asTable, newObj);
				obj.push_back(newObj);
				break;
			case OT_ARRAY:
				EncodeJsonArray<context>(node->_VAL.asArray, newArray);
				obj.push_back(newArray);
				break;
			default:
				spdlog::info("SQ encode Json type {} not supported", (int)node->_Type);
			}
		}
	}

	template <ScriptContext context> void
		DecodeJsonArray(HSquirrelVM* sqvm, nlohmann::json arr)
	{
		g_pSQManager<context>->NewArray(sqvm, 0);

		for (auto& itr : arr)
		{
			switch (itr.type())
			{
			case nlohmann::json::value_t::object:
				DecodeJsonTable<context>(sqvm, itr);
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::array:
				DecodeJsonArray<context>(sqvm, itr);
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::string:
				g_pSQManager<context>->PushString(sqvm, itr.get<std::string>().c_str(), -1);
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::boolean:
				g_pSQManager<context>->PushBool(sqvm, itr.get<bool>());
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::number_float:
				g_pSQManager<context>->PushFloat(sqvm, itr.get<float>());
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::number_integer:
			case nlohmann::json::value_t::number_unsigned:
				g_pSQManager<context>->PushInteger(sqvm, itr.get<int>());
				g_pSQManager<context>->ArrayAppend(sqvm, -2);
				break;
			case nlohmann::json::value_t::null:
				break;
			}
		}
	}

	template <ScriptContext context> void EncodeJsonTable(SQTable* table,
		nlohmann::json& obj)
	{
		for (int i = 0; i < table->_numOfNodes; i++)
		{
			tableNode* node = &table->_nodes[i];
			if (node->key._Type == OT_STRING)
			{
				nlohmann::json newObj = nlohmann::json::object();
				nlohmann::json newArray = nlohmann::json::array();

				const char* key = reinterpret_cast<const char*>(node->key._VAL.asString->_val);
				switch (node->val._Type)
				{
				case OT_STRING:
					obj[key] = reinterpret_cast<const char*>(node->val._VAL.asString->_val);
					break;
				case OT_INTEGER:
					obj[key] = node->val._VAL.asInteger;
					break;
				case OT_FLOAT:
					obj[key] = node->val._VAL.asFloat;
					break;
				case OT_BOOL:
					if (node->val._VAL.asInteger)
					{
						obj[key] = true;
					}
					else
					{
						obj[key] = false;
					}
					break;
				case OT_TABLE:
					EncodeJsonTable<context>(node->val._VAL.asTable, newObj);
					obj[key] = newObj;
					break;
				case OT_ARRAY:
					EncodeJsonArray<context>(node->val._VAL.asArray, newArray);
					obj[key] = newArray;
					break;
				default:
					spdlog::warn("SQ_EncodeJSON: squirrel type {} not supported", (int)node->val._Type);
					break;
				}
			}
		}
	}

	template <ScriptContext context> void
		DecodeJsonTable(HSquirrelVM* sqvm, nlohmann::json& obj)
	{
		g_pSQManager<context>->NewTable(sqvm);

		for (auto itr = obj.begin(); itr != obj.end(); itr++)
		{
			switch (itr.value().type())
			{
			case nlohmann::json::value_t::object:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				DecodeJsonTable<context>(
					sqvm, itr.value());
				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			case nlohmann::json::value_t::array:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				DecodeJsonArray<context>(
					sqvm, itr.value());
				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			case nlohmann::json::value_t::string:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				g_pSQManager<context>->PushString(sqvm, itr.value().get<std::string>().c_str(), -1);

				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			case nlohmann::json::value_t::boolean:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				g_pSQManager<context>->PushBool(sqvm, itr.value().get<bool>());
				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			case nlohmann::json::value_t::number_float:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				g_pSQManager<context>->PushFloat(sqvm, itr.value().get<float>());
				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			case nlohmann::json::value_t::number_integer:
			case nlohmann::json::value_t::number_unsigned:
				g_pSQManager<context>->PushString(sqvm, itr.key().c_str(), -1);
				g_pSQManager<context>->PushInteger(sqvm, itr.value().get<int>());
				g_pSQManager<context>->NewTableSlot(sqvm, -3, false);
				break;
			default:
				break;
			}
		}
	}

	template <ScriptContext context> SQRESULT Script_EncodeJSON(HSquirrelVM* sqvm)
	{
		SQTable* pTable = sqvm->_stackOfCurrentFunction[1]._VAL.asTable;
		const bool bFatalParseErrors = g_pSQManager<context>->GetBool(sqvm, 2);

		nlohmann::json doc;
		EncodeJsonTable<context>(pTable, doc);
		g_pSQManager<context>->PushString(sqvm, doc.dump().c_str(), -1);

		assert(doc.is_object());

		return SQRESULT_NOTNULL;
	}

	template <ScriptContext context> SQRESULT Script_DecodeJSON(HSquirrelVM* sqvm)
	{
		const char* pJson = g_pSQManager<context>->GetString(sqvm, 1);
		const bool bFatalParseErrors = g_pSQManager<context>->GetBool(sqvm, 2);

		nlohmann::json doc = nlohmann::json::parse(pJson, nullptr, false, false);
		if (doc.is_discarded())
		{
			g_pSQManager<context>->RaiseError(sqvm, "JSON passed in is invalid!");
			return SQRESULT_ERROR;
		}
		assert(doc.is_object());

		DecodeJsonTable<context>(sqvm, doc);

		return SQRESULT_NOTNULL;
	}
}