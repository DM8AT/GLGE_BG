/**
 * @file ConstexprHashmap.hpp
 * @author DM8AT
 * @brief a C++ only implementation of a constexpr capable, static sized hash map
 * @version 0.1
 * @date 2025-10-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
//header guard
#ifndef _GLGE_BG_CONSTEXPR_HASH_MAP_
#define _GLGE_BG_CONSTEXPR_HASH_MAP_

//only C++
#if __cplusplus

//add the size_t type
#include <stdlib.h>
//add std::arrays for more utilities
#include <array>

/**
 * @brief define a class that is used as a hash map with a constant size but it also works at compile time (constexpr capable)
 * 
 * @tparam Key the key to hash
 * @tparam Value the value to store at the key
 * @tparam Size the size of the entire hashmap
 */
template <typename Key, typename Value, size_t Size>
class Constexpr_HashMap
{
public:
    //ensure a sensible Size
    static_assert(Size > 0, "Constexpr_HashMap: Size must be > 0");
    /**
     * @brief store a pair of key and values
     */
    struct Pair {
        //the key that is hashed and used for indexing
        Key key;
        //the value to store
        Value value;
        //store if the value is occupied
        bool occupied = false;
    };

    /**
     * @brief default constructor for a hashmap
     */
    constexpr Constexpr_HashMap() noexcept = default;

    /**
     * @brief create a new constexpr capable hash map
     * 
     * @param init a list of values to initialize
     */
    constexpr Constexpr_HashMap(std::initializer_list<std::pair<Key, Value>> init) noexcept {
        //just store all the elements
        for (auto&& [key, value] : init) {
            if (!insert(key, value)) {
                //error if the map was full during creation
                static_assert(Size < SIZE_MAX, "Constexpr_HashMap overflow: table full during constexpr insert");
            }
        }
    }

    /**
     * @brief add a new element to the hash map
     * 
     * @param key the key of the element to add
     * @param value the value of the element to add
     * @return true : the element was successfully inserted
     * @return false : failed to insert the element - map too small
     */
    constexpr bool insert(const Key& key, const Value& value) noexcept {
        //store the index and first use the hash
        size_t idx = hash(key);

        //for collision resolving iterate over all elements in the hash map (potentially) and store the element only if it is free
        for (size_t i = 0; i < Size; ++i) {
            //use quadratic probing
            size_t probe = (idx + i*i) % Size;

            //check if the element is occupied or the elements aren't the same
            if (!m_data[probe].occupied || compareKey(m_data[probe].key, key)) {
                //store the key-value pair
                m_data[probe].key = key;
                m_data[probe].value = value;
                m_data[probe].occupied = true;
                //increase the amount of stored elements
                ++m_count;
                return true;
            }
        }

        //map full - failed to insert
        return false;
    }

    /**
     * @brief find a value by a key
     * 
     * @param key the key of the value to find
     * @return constexpr const Value* a constant pointer to the value or NULL if it is not found
     */
    constexpr const Value* find(const Key& key) const noexcept {
        //start by getting the hash of the key
        size_t idx = hash(key);
        //search the map for the key
        for (size_t i = 0; i < Size; ++i) {
            //use quadratic probing
            size_t probe = (idx + i*i) % Size;
            //check if this is the correct key
            if (!m_data[probe].occupied) 
                {return nullptr;}
            if (compareKey(m_data[probe].key, key))
                {return &m_data[probe].value;}
        }
        //not found
        return nullptr;
    }

    /**
     * @brief operator overload for easy access
     * 
     * @param key get the value of an element by the key
     * @return constexpr const Value* a pointer to the stored value
     */
    constexpr Value& operator[](const Key& key) {
        //get the element using find
        const Value* val = find(key);
        //if the element is not found, throw an error
        if (!val)
            throw std::out_of_range("Key not found in Constexpr_HashMap");
        //else, return the value
        return *((Value*)val);
    }

    /**
     * @brief get the amount of used elements in the hash map
     * 
     * @return constexpr size_t the amount of elements in the hash map
     */
    constexpr size_t size() const noexcept 
    {return m_count;}

protected:

    //store all optional elements
    std::array<Pair, Size> m_data{};
    //store the amount of elements
    size_t m_count = 0;

    /**
     * @brief compute the hash of a key value and make sure it is in range of the data
     * 
     * @param key the key to hash
     * @return constexpr size_t the resulting hash in range of the array
     */
    static constexpr size_t hash(const Key& key) noexcept {
        //change the hash depending on if the type is a integral (like int, uint64_t) or something else (assume string)
        if constexpr (std::is_integral_v<Key>) {
            //just use the value, but in range of the array
            return static_cast<size_t>(key) % Size;
        } else {
            //FNV-1a 64-bit variant, implemented constexpr-friendly
            //accepts any key type that is range-iterable (for (auto c : key)) or convertible to std::string_view
            //prefer keys with deterministic iteration (std::string, std::string_view, const char*)
            std::size_t h = 1469598103934665603ull;
            //if Key is directly convertible to std::string_view, use that (avoids requiring begin/end)
            if constexpr (std::is_convertible_v<Key, std::string_view>) {
                //use a hash for a string
                std::string_view sv(key);
                for (unsigned char c : sv) {
                    h = (h ^ static_cast<std::size_t>(c)) * 1099511628211ull;
                }
            } else {
                //try to iterate: requires Key to be range-iterable
                for (unsigned char c : key) {
                    h = (h ^ static_cast<std::size_t>(c)) * 1099511628211ull;
                }
            }
            //return the hash mapped to the size range
            return h % Size;
        }
    }

    /**
     * @brief compare if two keys are the same
     * 
     * @param a the first key
     * @param b the key to compare with
     * @return true : the keys are identical
     * @return false : the keys are not identical
     */
    static constexpr bool compareKey(const Key& a, const Key& b) {
        //switch depending on the type of key used
        if constexpr (std::is_integral_v<Key>) {
            //just use integral comparison
            return a == b;
        } else {
            //check if this is a string and use special comparisons
            if constexpr (std::is_convertible_v<Key, std::string_view>) {
                //use a special string comparison
                std::string_view sa(a);
                std::string_view sb(b);
                //if the length aren't the same, the string can#t be the same
                if (sa.size() != sb.size()) return false;
                //else, compare per element. Only if all elements are the same, the strings are the same
                for (std::size_t i = 0; i < sa.size(); ++i)
                {if (sa[i] != sb[i]) return false;}
                return true;
            } else {
                //fallback: iterate a and b simultaneously - require same length
                //.size() can't be called for arbitrary range, so compare element-by-element and ensure both end together
                auto itA = std::begin(a);
                auto itB = std::begin(b);
                auto endA = std::end(a);
                auto endB = std::end(b);
                for ( ; itA != endA && itB != endB; ++itA, ++itB) 
                {if (*itA != *itB) return false;}
                //true only if both reached end
                return (itA == endA) && (itB == endB);
            }
        }
    }

};

#endif

#endif