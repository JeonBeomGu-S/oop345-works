//
// Created by Beomgu Jeon on 2024-11-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//
#include <algorithm>
#include "collection.h"

namespace seneca {
    Collection::Collection(const std::string& name) {
        m_name = name;
    }
    Collection::~Collection() {
        for (auto item : m_mediaItems) {
            delete item;
        }
    }
    const std::string& Collection::name() const {
        return m_name;
    }
    size_t Collection::size() const {
        return m_mediaItems.size();
    }
    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        m_addObserver = observer;
    }
    Collection& Collection::operator+=(MediaItem* item) {
        bool isExist = std::any_of(m_mediaItems.begin(), m_mediaItems.end(), [item](MediaItem *mediaItem) {
            return item->getTitle() == mediaItem->getTitle();
        });
        if (!isExist) {
            m_mediaItems.push_back(item);
            if (m_addObserver)
                m_addObserver(*this, *item);
        } else {
            delete item;
        }
        return *this;
    }
    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_mediaItems.size()) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_mediaItems.size()) + "] items.");
        }
        return m_mediaItems[idx];
    }

    MediaItem* Collection::operator[](const std::string& title) const {
        auto iter = std::find_if(m_mediaItems.begin(), m_mediaItems.end(), [title](MediaItem *mediaItem) {
            return mediaItem->getTitle() == title;
        });
        if (iter != m_mediaItems.end()) {
            return *iter;
        } else {
            return nullptr;
        }
    }

    void Collection::removeQuotes() {
        std::transform(m_mediaItems.begin(), m_mediaItems.end(), m_mediaItems.begin(), [](MediaItem* mediaItem) {
            std::string title = mediaItem->getTitle();
            std::string summary = mediaItem->getSummary();

            if (!title.empty() && title.front() == '\"') {
                title.replace(0, 1, "");
            }
            if (!title.empty() && title.back() == '\"') {
                title.replace(title.length() - 1, 1, "");
            }
            if (!summary.empty() && summary.front() == '\"') {
                summary.replace(0, 1, "");
            }
            if (!summary.empty() && summary.back() == '\"') {
                summary.replace(summary.length() - 1, 1, "");
            }
            mediaItem->setTitle(title);
            mediaItem->setSummary(summary);
            return mediaItem;
        });
    }

    void Collection::sort(const std::string& field) {
        std::sort(m_mediaItems.begin(), m_mediaItems.end(), [field](MediaItem* mediaItem1, MediaItem* mediaItem2) {
            if (field == "title") {
                return mediaItem1->getTitle() < mediaItem2->getTitle();
            } else if (field == "year") {
                return mediaItem1->getYear() < mediaItem2->getYear();
            } else if (field == "summary") {
                return mediaItem1->getSummary() < mediaItem2->getSummary();
            } else {
                return mediaItem1 < mediaItem2;
            }
        });
    }

    std::ostream& operator<<(std::ostream& os, const Collection& item) {
        for (size_t i = 0; i < item.size(); ++i) {
            item[i]->display(os);
        }
        return os;
    }
}