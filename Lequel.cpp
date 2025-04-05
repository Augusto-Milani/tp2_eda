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
 
     for (auto line : text) {    //Each line of text

         // Tip: converts UTF-8 string to wstring
         wstring unicodeString = converter.from_bytes(line);

         while ((unicodeString.length() >= 3)   &&   (unicodeString[unicodeString.length() - 1] == '\r')) {

            wstring wstrTrigram = unicodeString;

            while ( (wstrTrigram.length() > 3)   &&   
                    (wstrTrigram[wstrTrigram.length() - 1] == '\r') ) { //If there's more than 3 characters in line,
                wstrTrigram = wstrTrigram.substr(0, wstrTrigram.length() - 1);   // substracts last character from line.
            }  

            if(wstrTrigram.length() == 3) {
                // Tip: convert wstring to UTF-8 string
                string trigram = converter.to_bytes(wstrTrigram);
                profile[trigram] += 1.0F;    //Frequency of trigram is incremented by one.
            }

            unicodeString = unicodeString.substr(0, 0);   // substracts first character from line.
        }
            
    }
    return TrigramProfile(profile);
 }
 
 /**
  * @brief Normalizes a trigram profile.
  *
  * @param trigramProfile The trigram profile.
  */
void normalizeTrigramProfile(TrigramProfile &trigramProfile)
{
    float sumFreqSquare = 0;
    for(auto &element : trigramProfile) {
        sumFreqSquare += pow(element.second, 2);
    }

    for(auto &element : trigramProfile) {
        element.second /= sqrt(sumFreqSquare);
    }

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
    float similarity = 0;

    for(auto elementText : textProfile) {
        for(auto elementLanguage : languageProfile) {

            if (elementText.first == elementLanguage.first) {   //Compares if the string given exists in both profiles
                similarity += elementText.second * elementLanguage.second;  //Sum the product of frequencies
                break;  //No need to continue searching for the string.
            }
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
     // Your code goes here...
 
     return ""; // Fill-in result here
 }
 