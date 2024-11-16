//
// Created by Beomgu Jeon on 2024-11-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <vector>
#include "mediaItem.h"

namespace seneca {
    class Collection {
        std::string m_name{};
        std::vector<MediaItem*> m_mediaItems{};
        void (*m_addObserver)(const Collection& collection, const MediaItem& mediaItem){};

    public:
        Collection(const std::string& name);
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;
        ~Collection();
        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem *item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();
        void sort(const std::string& field);
    };

    std::ostream& operator<<(std::ostream& os, const Collection& item);
}

#endif // SENECA_COLLECTION_H
