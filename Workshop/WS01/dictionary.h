//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <iostream>
#include <string>

namespace seneca {
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word {
        std::string m_word {};
        std::string m_definition {};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class dictionary {
        Word* m_wordList{nullptr};
        int m_numberOfWords{};
    public:
        dictionary();
        dictionary(const char* filename);
        // rule of 5
        // CC / CA
        dictionary(const dictionary& src);
        dictionary& operator=(const dictionary& src);
        // MC / MA
        dictionary(dictionary&& src);
        dictionary& operator=(dictionary&& src);
        // Destructor
        ~dictionary();
        void searchWord(const char* word);
    };
}


#endif //SENECA_DICTIONARY_H
