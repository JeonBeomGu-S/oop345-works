//
// Created by Beomgu Jeon on 2024-11-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <iostream>
#include <string>
#include "mediaItem.h"

namespace seneca {
    class Movie : public MediaItem {
        Movie(const std::string& title, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };
}


#endif // SENECA_MOVIE_H
