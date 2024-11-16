//
// Created by Beomgu Jeon on 2024-11-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include <algorithm>
#include <numeric>
#include "tvShow.h"
#include "settings.h"

namespace seneca {
    TvShow::TvShow(const std::string &id, const std::string &title, unsigned short year, const std::string &summary) : MediaItem(title, summary, year) {
        m_id = id;
    }

    void TvShow::display(std::ostream &out) const {
        if (g_settings.m_tableView) {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            } else
                out << this->getSummary();
            out << std::endl;
        } else {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto &item: m_episodes) {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size()) {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow.front() == '#') {
            throw "Not a valid show.";
        }

        size_t start{};
        size_t end{};
        size_t index = 0;
        std::string str[4];

        while (end != std::string::npos) {
            if (index > 3) {
                break;
            }
            start = end != 0 ? end + 1 : 0;
            end = strShow.find(',', start);
            std::string temp;
            if (index != 3) {
                temp = strShow.substr(start, (end - start));
            } else {
                temp = strShow.substr(start);
            }
            trim(temp);
            str[index] = temp;
            index++;
        }

        return new TvShow(str[0], str[1], std::stoi(str[2]), str[3]);
    }

    double TvShow::getEpisodeAverageLength() const {
        double sum = std::accumulate(m_episodes.begin(), m_episodes.end(), 0, [](const int& result, const TvEpisode& episode) {
            return result + episode.m_length;
        });

        return sum / m_episodes.size();
    }
    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> longEpisodes;

        std::for_each(m_episodes.begin(), m_episodes.end(), [&longEpisodes](const TvEpisode& episode) {
            if (episode.m_length >= 3600)
                longEpisodes.push_back(episode.m_title);
        });

        return longEpisodes;
    }
}