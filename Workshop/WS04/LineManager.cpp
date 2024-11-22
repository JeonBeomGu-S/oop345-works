//
// Created by Beomgu Jeon on 2024-11-21.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <fstream>
#include <algorithm>
#include <numeric>
#include "Utilities.h"
#include "LineManager.h"

namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        Utilities util;
        std::ifstream ifs(file);
        std::string record;
        while (std::getline(ifs, record)) {
            size_t nextPos {0};
            bool more = true;

            std::string first = util.extractToken(record, nextPos, more);
            std::string second = more ? util.extractToken(record, nextPos, more) : "";

            Workstation* firstWorkstation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
               return station->getItemName() == first;
            });

            Workstation* secondWorkstation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == second;
            });

            if (secondWorkstation) {
                firstWorkstation->setNextStation(secondWorkstation);
                m_activeLine.push_back(firstWorkstation);
            } else {
                firstWorkstation->setNextStation(nullptr);
                m_activeLine.push_back(firstWorkstation);
            }
        }


        for (auto & i : m_activeLine) {
            std::string itemName = i->getItemName();
            bool isFound = false;
            for (auto & j : m_activeLine) {
                if (j->getNextStation() && itemName == j->getNextStation()->getItemName()) {
                    isFound = true;
                    break;
                }
            }
            if (!isFound) {
                m_firstStation = i;
            }
        }

        /*
            Bed --> Dresser --> Armchair --> Nighttable --> Desk --> Office Chair --> Filing Cabinet --> Bookcase
         */

        m_cntCustomerOrder = g_pending.size();
        ifs.close();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> newActiveLines;
        std::string nextItemName = m_firstStation->getNextStation()->getItemName();
        newActiveLines.push_back(m_firstStation);

        while (newActiveLines.size() < m_activeLine.size()) {
            std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *station) {
                if (nextItemName == station->getItemName()) {
                    newActiveLines.push_back(station);
                    if (station->getNextStation())
                        nextItemName = station->getNextStation()->getItemName();
                }
            });
        }

        m_activeLine = newActiveLines;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iterNum = 1;

        os << "Line Manager Iteration: " << iterNum << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* station) {
            station->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station) {
            station->attemptToMoveOrder();
        });

        iterNum++;

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station) {
            station->display(os);
        });
    }
}