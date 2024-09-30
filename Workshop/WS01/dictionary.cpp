//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <fstream>
#include <sstream>
#include <cstring>
#include "settings.h"
#include "dictionary.h"

namespace seneca {
    Dictionary::Dictionary() {

    }

    Dictionary::Dictionary(const char *filename) {
        std::ifstream is(filename);
        if (is.is_open()) {
            std::string temp;
            int numberOfWords = 0;
            while (getline(is, temp)) {
                numberOfWords++;
            }
            m_wordList = new Word[numberOfWords];
            m_numberOfWords = numberOfWords;

            int idx = 0;
            is.clear();
            is.seekg(0, std::ios::beg);
            while (getline(is, temp)) {
                std::string field;
                std::stringstream ss(temp);

                // word
                getline(ss, field, ',');
                m_wordList[idx].m_word = field;

                // pos
                getline(ss, field, ',');
                if (field == "n." || field == "n. pl.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Noun;
                } else if (field == "adv.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Adverb;
                } else if (field == "a.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Adjective;
                } else if (field == "v." || field == "v. i." || field == "v. t." || field == "v. t. & i.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Verb;
                } else if (field == "prep.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Preposition;
                } else if (field == "pron.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Pronoun;
                } else if (field == "conj.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Conjunction;
                } else if (field == "interj.") {
                    m_wordList[idx].m_pos = PartOfSpeech::Interjection;
                } else {
                    m_wordList[idx].m_pos = PartOfSpeech::Unknown;
                }

                // definition
                getline(ss, field, '\n');
                m_wordList[idx].m_definition = field;

                idx++;
            }
        } else {
            delete[] m_wordList;
            m_wordList = nullptr;
        }
    }

    void Dictionary::searchWord(const char *word) {
        bool isFound = false;
        for (int i = 0; i < m_numberOfWords; i++) {
            if (m_wordList[i].m_word == word) {
                if (!isFound) {
                    std::cout << word << " - ";
                    isFound = true;
                } else {
                    std::cout.width(strlen(word) + 3);
                    std::cout << std::right << " - ";
                }
                if (seneca::g_settings.m_verbose) {
                    switch (m_wordList[i].m_pos) {
                        case PartOfSpeech::Unknown:
                            break;
                        case PartOfSpeech::Noun:
                            std::cout << "(noun) ";
                            break;
                        case PartOfSpeech::Adverb:
                            std::cout << "(adverb) ";
                            break;
                        case PartOfSpeech::Adjective:
                            std::cout << "(adjective) ";
                            break;
                        case PartOfSpeech::Verb:
                            std::cout << "(verb) ";
                            break;
                        case PartOfSpeech::Preposition:
                            std::cout << "(preposition) ";
                            break;
                        case PartOfSpeech::Pronoun:
                            std::cout << "(pronoun) ";
                            break;
                        case PartOfSpeech::Conjunction:
                            std::cout << "(conjunction) ";
                            break;
                        case PartOfSpeech::Interjection:
                            std::cout << "(interjection) ";
                            break;
                    }
                }

                std::cout << m_wordList[i].m_definition << std::endl;
                if (isFound && !seneca::g_settings.m_show_all) {
                    break;
                }
            }
        }

        if (!isFound) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

    Dictionary::Dictionary(const Dictionary& src) {
        *this = src;
    }
    Dictionary& Dictionary::operator=(const Dictionary& src) {
        if (this != &src) {
            if (m_wordList) {
                delete[] m_wordList;
                m_wordList = nullptr;
            }

            m_numberOfWords = src.m_numberOfWords;
            m_wordList = new Word[m_numberOfWords];

            for (int i = 0; i < m_numberOfWords; ++i) {
                m_wordList[i] = src.m_wordList[i];
            }
        }

        return *this;
    }
    Dictionary::Dictionary(Dictionary&& src) {
        *this = std::move(src);
    }

    Dictionary& Dictionary::operator=(Dictionary&& src) {
        if (this != &src) {
            if (m_wordList) {
                delete[] m_wordList;
                m_wordList = nullptr;
            }

            m_numberOfWords = src.m_numberOfWords;
            m_wordList = src.m_wordList;

            src.m_numberOfWords = 0;
            src.m_wordList = nullptr;
        }

        return *this;
    }
    Dictionary::~Dictionary() {
        delete[] m_wordList;
    }
}