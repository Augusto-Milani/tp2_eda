/**
 * @brief Lequel? language identification based on trigrams
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 *
 * @cite https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 */

#include <cmath>
#include <codecvt>
#include <locale>
#include <iostream>

#include "Lequel.h"

using namespace std;

/**
 * @brief Builds a trigram profile from a given text.
 *
 * @param text Vector of lines (Text)
 * @return TrigramProfile The trigram profile
 */
TrigramProfile buildTrigramProfile(const Text &text)
{
    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    
    TrigramProfile profile;

    for (auto line : text) {    //Each possible substring,
        for (auto line : text) {    // with 3 characters.
            if ((line.length() > 3)   &&   (line[line.length() - 1] == '\r')) { //If there's more than 3 characters in line,
                line = line.substr(0, line.length() - 1);   // substracts last character from line.
            }
        }
        profile[line] += 1.0F;    //Frequency of substring is incremented by one.
        
        // Tip: converts UTF-8 string to wstring
        wstring unicodeString = converter.from_bytes(textLine);

        // Tip: convert wstring to UTF-8 string
        string trigram = converter.to_bytes(unicodeTrigram);
        
        if ((line.length() > 3)   &&   (line[line.length() - 1] == '\r')) {
            line = line.substr(0, 0);   // substracts first character from line.
        }
    } 
    return TrigramProfile(profile); // Fill-in result here
}

/**
 * @brief Normalizes a trigram profile.
 *
 * @param trigramProfile The trigram profile.
 */
void normalizeTrigramProfile(TrigramProfile &trigramProfile)
{
    // Your code goes here...

    return;
}

/**
 * @brief Calculates the cosine similarity between two trigram profiles
 *
 * @param textProfile The text trigram profile
 * @param languageProfile The language trigram profile
 * @return float The cosine similarity score
 */
float getCosineSimilarity(TrigramProfile &textProfile, TrigramProfile &languageProfile)
{
    // Your code goes here...

    return 0; // Fill-in result here
}

/**
 * @brief Identifies the language of a text.
 *
 * @param text A Text (vector of lines)
 * @param languages A list of Language objects
 * @return string The language code of the most likely language
 */
string identifyLanguage(const Text &text, LanguageProfiles &languages)
{
    // Your code goes here...

    return ""; // Fill-in result here
}
