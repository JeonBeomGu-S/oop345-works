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

    class Dictionary {
        Word* m_wordList{nullptr};
        int m_numberOfWords{};
    public:
        Dictionary();
        Dictionary(const char* filename);
        // rule of 5
        // CC / CA
        Dictionary(const Dictionary& src);
        Dictionary& operator=(const Dictionary& src);
        // MC / MA
        Dictionary(Dictionary&& src);
        Dictionary& operator=(Dictionary&& src);
        // Destructor
        ~Dictionary();
        void searchWord(const char* word);
    };
}


#endif //SENECA_DICTIONARY_H
