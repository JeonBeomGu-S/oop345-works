//
// Created by Beomgu Jeon on 2024-11-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "mediaItem.h"

namespace seneca {
    class TvShow;

    struct TvEpisode {
        const TvShow *m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;
        TvShow(const std::string& id, const std::string &title, unsigned short year, const std::string &summary);

    public:
        void display(std::ostream &out) const override;
        static TvShow* createItem(const std::string& strShow);
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            size_t start{};
            size_t end{};
            size_t index = 0;
            std::string str[8];

            if (strEpisode.empty() || strEpisode.front() == '#') {
                throw "Not a valid episode.";
            }

            while (end != std::string::npos) {
                if (index > 7) {
                    break;
                }
                start = end != 0 ? end + 1 : 0;
                end = strEpisode.find(',', start);
                std::string temp;
                if (index != 7) {
                    temp = strEpisode.substr(start, (end - start));
                } else {
                    temp = strEpisode.substr(start);
                }
                trim(temp);
                str[index] = temp;
                index++;
            }

            unsigned short length = std::stoi(str[5].substr(0, 2)) * 3600
                                    + std::stoi(str[5].substr(3, 2)) * 60
                                    + std::stoi(str[5].substr(6, 2));

            TvShow *tvShow = nullptr;
            for (size_t i = 0; i < col.size(); ++i) {
                if (str[0] == dynamic_cast<TvShow *>(col[i])->m_id) {
                    tvShow = dynamic_cast<TvShow *>(col[i]);
                    break;
                }
            }


            TvEpisode t{tvShow,
                        static_cast<unsigned short>((std::stoi(str[1]))),
                        str[2] == "" ? (unsigned short) 1 : static_cast<unsigned short>((std::stoi(str[2]))),
                        static_cast<unsigned short>((std::stoi(str[3]))),
                        str[4],
                        length,
                        str[6],
                        str[7],
            };
            if (tvShow) {
                tvShow->m_episodes.push_back(t);
            }
        }
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
}

#endif // SENECA_TVSHOW_H
