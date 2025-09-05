/**
 * @file String.cpp
 * @author DM8AT
 * @brief implement the String compatibility layer
 * @version 0.1
 * @date 2025-09-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the string capacity layer
#include "String.h"

String* string_Create() {return new String();}

String* string_CreateFrom(const char* str) {return new String(str);}

String* string_CreateCopy(const String* str) {return new String(*str);}

void string_Destroy(String* str) {delete str;}

char string_Get(uint64_t i, String* str) {return str->at(i);}

char string_Front(String* str) {return str->front();}

char string_Back(String* str) {return str->back();}

char* string_Data(String* str) {return str->data();}

const char* string_C_Str(String* str) {return str->c_str();}

bool string_Emtpy(String* str) {return str->empty();}

uint64_t string_Size(String* str) {return str->size();}

uint64_t string_Length(String* str) {return str->length();}

uint64_t string_Max_size(String* str) {return str->max_size();}

uint64_t string_Capacity(String* str) {return str->capacity();}

void string_Shrink_to_fit(String* str) {return str->shrink_to_fit();}

void string_Clear(String* str) {str->clear();}

void string_InsertChar(uint64_t idx, char character, uint64_t count, String* str) {str->insert(idx, count, character);}

void string_InsertCString(uint64_t idx, const char* string, String* str) {str->insert(idx, string);}

void string_InsertString(uint64_t idx, String* insert, String* str) {str->insert(idx, *insert);}

void string_Erase(uint64_t idx, String* str) {str->erase(idx);}

void string_EraseCount(uint64_t idx, uint64_t count, String* str) {str->erase(idx, count);}

void string_Push_back(char character, String* str) {str->push_back(character);}

void string_Pop_back(String* str) {str->pop_back();}

void string_AppendChar(char character, uint64_t count, String* str) {str->append(count, character);}

void string_AppendCString(const char* string, uint64_t count, String* str) {str->append(string, count);}

void string_AppendString(String* string, uint64_t count, String* str) {str->append(*string, count);}

void string_ReplaceChar(uint64_t pos, uint64_t len, uint64_t count, char character, String* str) {str->replace(pos, len, count, character);}

void string_ReplaceCString(uint64_t pos, uint64_t len, const char* string, String* str) {str->replace(pos, len, string);}

void string_ReplaceString(uint64_t pos, uint64_t len, String* string, String* str) {str->replace(pos, len, *string);}

void string_Copy(char* storage, uint64_t len, uint64_t pos, String* str) {str->copy(storage, len, pos);}

void string_Reserve(uint64_t size, String* str) {str->reserve(size);}

void string_Resize(uint64_t size, String* str) {str->resize(size);}

void string_Swap(String* string, String* str) {str->swap(*string);}

uint64_t string_FindChar(uint64_t pos, char character, String* str) {return str->find(character, pos);}

uint64_t string_FindCString(uint64_t pos, const char* string, String* str) {return str->find(string, pos);}

uint64_t string_FindString(uint64_t pos, String* string, String* str) {return str->find(*string, pos);}

uint64_t string_RFindChar(uint64_t pos, char character, String* str) {return str->rfind(character, pos);}

uint64_t string_RFindCString(uint64_t pos, const char* string, String* str) {return str->rfind(string, pos);}

uint64_t string_RFindString(uint64_t pos, String* string, String* str) {return str->rfind(*string, pos);}

uint64_t string_Find_first_ofChar(uint64_t pos, char character, String* str) {return str->find_first_of(character, pos);}

uint64_t string_Find_first_ofCString(uint64_t pos, const char* string, String* str) {return str->find_first_of(string, pos);}

uint64_t string_Find_first_ofString(uint64_t pos, String* string, String* str) {return str->find_first_of(*string, pos);}

uint64_t string_Find_first_not_ofChar(uint64_t pos, char character, String* str) {return str->find_first_not_of(character, pos);}

uint64_t string_Find_first_not_ofCString(uint64_t pos, const char* string, String* str) {return str->find_first_not_of(string, pos);}

uint64_t string_Find_first_not_ofString(uint64_t pos, String* string, String* str) {return str->find_first_not_of(*string, pos);}

uint64_t string_Find_last_ofChar(uint64_t pos, char character, String* str) {return str->find_last_of(character, pos);}

uint64_t string_Find_last_ofCString(uint64_t pos, const char* string, String* str) {return str->find_last_of(string, pos);}

uint64_t string_Find_last_ofString(uint64_t pos, String* string, String* str) {return str->find_last_of(*string, pos);}

uint64_t string_Find_last_not_ofChar(uint64_t pos, char character, String* str) {return str->find_last_not_of(character, pos);}

uint64_t string_Find_last_not_ofCString(uint64_t pos, const char* string, String* str) {return str->find_last_not_of(string, pos);}

uint64_t string_Find_last_not_ofString(uint64_t pos, String* string, String* str) {return str->find_last_not_of(*string, pos);}

String* string_Substring(uint64_t pos, uint64_t len, String* str) {return new String(str->substr(pos, len));}