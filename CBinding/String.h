/**
 * @file String.h
 * @author DM8AT
 * @brief define a C binding for a string wrapper
 * @version 0.1
 * @date 2025-09-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_C_STRING_
#define _GLGE_C_STRING_

#include <stdint.h>

#if __cplusplus
#include <string>
#endif

//check for C++. There, a string is a std::string. On C, a string is an opaque struct. 
#if __cplusplus
/**
 * @brief store a string for the C/C++ compat library
 */
typedef std::string String;
#else
typedef struct s_String String;
#endif

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new, empty string object
 * 
 * @return String* a pointer to the new string object
 */
String* string_Create();

/**
 * @brief create a string that contains a given c string
 * 
 * @param str the c string to fill the inital string with
 * @return String* a pointer to the new string object
 */
String* string_CreateFrom(const char* str);

/**
 * @brief create a string that contains a copy of another string
 * 
 * @param str the string to copy
 * @return String* the new string object
 */
String* string_CreateCopy(const String* str);

/**
 * @brief delete a string object
 * 
 * @param str a pointer to the string object to delete
 */
void string_Destroy(String* str);

/**
 * @brief get a specific character from the string
 * 
 * @param i the zero based index of the character to quarry
 * @param str a pointer to the string to quarry the character from
 * @return char the character at that position
 */
char string_Get(uint64_t i, String* str);

/**
 * @brief get the first character from a string
 * 
 * @param str a pointer to the string object
 * @return char the first character of the string
 */
char string_Front(String* str);

/**
 * @brief get the last character from a string
 * 
 * @param str a pointer to the string object
 * @return char the last character of the string (before the NULL character)
 */
char string_Back(String* str);

/**
 * @brief get the raw data from a string
 * 
 * @param str a pointer to the string object
 * @return char* the raw string data
 */
char* string_Data(String* str);

/**
 * @brief get a c string from a string
 * 
 * @param str a pointer to the string object
 * @return const char* a null terminated c string
 */
const char* string_C_Str(String* str);

/**
 * @brief check if a string is empty
 * 
 * @param str a pointer to the string object
 * @return true : the string object is empty
 * @return false : the string object is not empty
 */
bool string_Emtpy(String* str);

/**
 * @brief get the size (length) of a string object
 * 
 * @param str a pointer to the string object
 * @return uint64_t the length of the string object without null termination character
 */
uint64_t string_Size(String* str);

/**
 * @brief get the length of a string object
 * 
 * @param str a pointer to the string object
 * @return uint64_t the length of the string object without null termination character
 */
uint64_t string_Length(String* str);

/**
 * @brief get the maximal theoretical length of a string object
 * 
 * @param str a pointer to the string object
 * @return uint64_t the maximum theoretical length the string object can reach
 */
uint64_t string_Max_size(String* str);

/**
 * @brief get the capacity of a string object. That is the maximum length (including the null character) the string can reach before re-allocating memory
 * 
 * @param str a pointer to the string object
 * @return uint64_t the capacity of the string object
 */
uint64_t string_Capacity(String* str);

/**
 * @brief shrink the capacity of a string to fit the length
 * 
 * @param str a pointer to the string object
 */
void string_Shrink_to_fit(String* str);

/**
 * @brief clear the contents from a string object
 * 
 * @param str a pointer to the string object
 */
void string_Clear(String* str);

/**
 * @brief insert a character or multiple characters at a specific position in the string
 * 
 * @param idx the index to start the insertion at
 * @param character the character to insert
 * @param count the amount of characters to insert
 * @param str a pointer to the string object
 */
void string_InsertChar(uint64_t idx, char character, uint64_t count, String* str);

/**
 * @brief insert a c string at a specific index into a string object
 * 
 * @param idx the index to start the insertion at
 * @param string the c string to insert
 * @param str a pointer to the string object
 */
void string_InsertCString(uint64_t idx, const char* string, String* str);

/**
 * @brief insert another string object into a string object at a specific index
 * 
 * @param idx the index to start the insertion at
 * @param insert the string object to insert
 * @param str a pointer to the string object
 */
void string_InsertString(uint64_t idx, String* insert, String* str);

/**
 * @brief erase a single character from a string object
 * 
 * @param idx the index of the character to erase
 * @param str a pointer to the string object
 */
void string_Erase(uint64_t idx, String* str);

/**
 * @brief erase a range of characters from a string object
 * 
 * @param idx the index to start the erasing from
 * @param count the amount of characters to erase
 * @param str a pointer to the string object
 */
void string_EraseCount(uint64_t idx, uint64_t count, String* str);

/**
 * @brief add a single character at the end of a string object
 * 
 * @param character the character to add at the end of a string object
 * @param str a pointer to the string object
 */
void string_Push_back(char character, String* str);

/**
 * @brief erase a single character from tne end of a string object
 * 
 * @param str a pointer to the string object
 */
void string_Pop_back(String* str);

/**
 * @brief add a single character to the end of a string object
 * 
 * @param character the character to append at the end of the string object
 * @param count the amount of characters to append
 * @param str a pointer to the string object
 */
void string_AppendChar(char character, uint64_t count, String* str);

/**
 * @brief append a c string to the end of a string object
 * 
 * @param string the string object to append to the end of the string
 * @param count the amount of characters to append at the end
 * @param str a pointer to the string object
 */
void string_AppendCString(const char* string, uint64_t count, String* str);

/**
 * @brief append a string object to the end of another string object
 * 
 * @param string the string object to append at the end of the other string object
 * @param count the amount of characters to append to the end of the string object
 * @param str a pointer to the string object
 */
void string_AppendString(String* string, uint64_t count, String* str);

/**
 * @brief replace a section of the string object with specified characters
 * 
 * @param pos the position in the string to start the insertion at
 * @param len the number of characters to replace
 * @param count the number of characters to insert
 * @param character the character to insert into the string object
 * @param str a pointer to the string object
 */
void string_ReplaceChar(uint64_t pos, uint64_t len, uint64_t count, char character, String* str);

/**
 * @brief replace a section of a string object with a section of a c string
 * 
 * @param pos the position to start the insertion at
 * @param len the number of characters to replace
 * @param string the c string to insert the characters from
 * @param str a pointer to the string object
 */
void string_ReplaceCString(uint64_t pos, uint64_t len, const char* string, String* str);

/**
 * @brief replace a section of a string object with a section of another string object
 * 
 * @param pos the position to start the insertion at
 * @param len the number of characters to replace
 * @param string the string object to insert the characters from
 * @param str a pointer to the string object
 */
void string_ReplaceString(uint64_t pos, uint64_t len, String* string, String* str);

/**
 * @brief copy a section of the string object into an external storage
 * 
 * @param storage the storage to store the elements into. Must be large enough to store all elements. 
 * @param len the length of the section to copy
 * @param pos the position to start the copying at
 * @param str a pointer to the string object
 */
void string_Copy(char* storage, uint64_t len, uint64_t pos, String* str);

/**
 * @brief pre-reserve a specific size of elements for a string object
 * 
 * @param size the size to reserve for the string object
 * @param str a pointer to the string object
 */
void string_Reserve(uint64_t size, String* str);

/**
 * @brief change the size of a string object
 * 
 * @param size the size to change the string object to
 * @param str a pointer to the string object
 */
void string_Resize(uint64_t size, String* str);

/**
 * @brief swap the contents of two string objects
 * 
 * @param string the string object to swap with
 * @param str a pointer to the string object to swap to
 */
void string_Swap(String* string, String* str);

/**
 * @brief find the position of a specific character
 * 
 * @param pos the position to start the search from
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the found element or UINT64_MAX if the element is not found
 */
uint64_t string_FindChar(uint64_t pos, char character, String* str);

/**
 * @brief find a specific sub-string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the c-string to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the found element or UINT64_MAX if the element is not found
 */
uint64_t string_FindCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find a specific sub-string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the string object to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the found element or UINT64_MAX if the element is not found
 */
uint64_t string_FindString(uint64_t pos, String* string, String* str);

/**
 * @brief find the position of the last occurrence of a specific character
 * 
 * @param pos the position to start the search from
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element or UINT64_MAX if the element is not found
 */
uint64_t string_RFindChar(uint64_t pos, char character, String* str);

/**
 * @brief find the position of the last occurrence of a specific sub-string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the c-string to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element or UINT64_MAX if the element is not found
 */
uint64_t string_RFindCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find the position of the last occurrence of a specific sub-string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the string object to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element or UINT64_MAX if the element is not found
 */
uint64_t string_RFindString(uint64_t pos, String* string, String* str);

/**
 * @brief find the first occurrence of a character in a string object
 * 
 * @param pos the position to start the search at
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_ofChar(uint64_t pos, char character, String* str);

/**
 * @brief find the first occurrence of a c string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_ofCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find the first occurrence of a c string in a string object
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_ofString(uint64_t pos, String* string, String* str);

/**
 * @brief find the first element that is not a specific character
 * 
 * @param pos the position to start the search at
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element that is NOT the inputted character or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_not_ofChar(uint64_t pos, char character, String* str);

/**
 * @brief find the first element that is not a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element that is NOT the inputted substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_not_ofCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find the first element that is not a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the first found element that is NOT the inputted substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_first_not_ofString(uint64_t pos, String* string, String* str);

/**
 * @brief find the last occurrence of a specific character
 * 
 * @param pos the position to start the search at
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is character or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_ofChar(uint64_t pos, char character, String* str);

/**
 * @brief find the last occurrence of a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_ofCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find the last occurrence of a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_ofString(uint64_t pos, String* string, String* str);

/**
 * @brief find the last occurrence that is not of a specific character
 * 
 * @param pos the position to start the search at
 * @param character the character to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is NOT the inputted character or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_not_ofChar(uint64_t pos, char character, String* str);

/**
 * @brief find the last occurrence that is not of a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is NOT the inputted substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_not_ofCString(uint64_t pos, const char* string, String* str);

/**
 * @brief find the last occurrence that is not of a specific substring
 * 
 * @param pos the position to start the search at
 * @param string the substring to search for
 * @param str a pointer to the string object
 * @return uint64_t the position of the last found element that is NOT the inputted substring or UINT64_MAX if the element is not found
 */
uint64_t string_Find_last_not_ofString(uint64_t pos, String* string, String* str);

/**
 * @brief create a new string by getting a subsection of a string
 * 
 * @param pos the position to start the substring from
 * @param len the length of the substring to extract
 * @param str a pointer to the string object
 * @return String* a pointer to a new string that contains a subsection of the string
 */
String* string_Substring(uint64_t pos, uint64_t len, String* str);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif