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
 #include <vector>

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

     for (auto line : text) {
        // convierte a wstring la linea
         std::wstring unicodeString = converter.from_bytes(line);

         //si tiene 3  o mas caracteres...
         while (unicodeString.length() >= 3) {
            std::wstring wstrTrigram = unicodeString;

            //saco todos los caracteres menos los primeros 3
            while (wstrTrigram.length() > 3) {
                wstrTrigram = wstrTrigram.substr(0, wstrTrigram.length() - 1);
            }

            // lo vuelvo a convertir a string
            std::string trigram = converter.to_bytes(wstrTrigram);
            profile[trigram] += 1.0F;
            // SI ESE TRIGRAMA YA FUE GUARDADO, ENTONCES LE VOY A ESTAR AUMENTANDO LA FRECUENCIA

            unicodeString = unicodeString.substr(1);   // substracts first character from line.
        }
    }
    return profile;
 }
 
 /**
  * @brief Normalizes a trigram profile.
  *
  * @param trigramProfile The trigram profile.
  */
bool normalizeTrigramProfile(TrigramProfile &trigramProfile)
{
    float sumFreqSquare = 0;
    vector<float> frequencies;
    
    //it is more efficient to loop through and access a vector than a map
    for (auto trigramToCopyFrequencyFrom : trigramProfile) 
        frequencies.push_back(trigramToCopyFrequencyFrom.second);

    for(auto &element : frequencies)
        sumFreqSquare += element * element;

    if (!sumFreqSquare) {
        perror("Invalid trigram profile");
        return false;
    }

    for(auto &element : frequencies)
        element /= sqrt(sumFreqSquare);

    return true;
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
    float similarity = 0.0;

    for (auto &textTrigram : textProfile) {
        auto currentTrigram = languageProfile.find(textTrigram.first);
        if (currentTrigram != languageProfile.end()) {
            similarity += textTrigram.second * currentTrigram->second;
        }
    }
    return similarity;
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
    std::string result;
    float cosineSimilarity, similarity = 0;

    TrigramProfile profile = buildTrigramProfile(text);
    
    if (!normalizeTrigramProfile(profile))
        return "";

    else {
        for (auto language : languages) {
            cosineSimilarity = getCosineSimilarity(profile, language.trigramProfile); // language.trigramProfile ya estaba normalizado

            if (cosineSimilarity > similarity) {
                similarity = cosineSimilarity;
                result = language.languageCode;
            }
        }

        return result;
    }
}
 