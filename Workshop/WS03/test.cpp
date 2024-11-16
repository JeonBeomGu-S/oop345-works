//
// Created by Beomgu Jeon on 2024-11-05.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// #define ex1 // find(const string& str)
// #define ex2 // find(const string& str, size_t pos)
// #define ex3 // find(const string& str, size_t pos) & string::npos
// #define ex4 // algorithm loop (for_each, max_element)
#define ex5 //

using namespace std;

struct Movie {
    string title{};
    string genre{};
    int runtime;
};

int main() {
    ifstream fin("src.txt");
    string str;
    getline(fin, str);

    cout << "str: " << str << endl;

    string first{};
    int second{};
    double third{};
    string fourth{};

    // first = str.substr(0, 3); // get till i see a comma
    // need to know where the comma is by a position
#ifdef ex1
    size_t pos{};
    pos = str.find(',');
    cout << "pos: " << pos << endl;
    first = str.substr(0, pos);
    cout << "first: " << first << endl;
#endif
#ifdef ex2
    size_t start{};
    size_t end{};

    end = str.find(',');
    cout << "end: " << end << endl;

    first = str.substr(start, end);
    cout << "first: " << first << endl;

    start = end + 1;
    end = str.find(',', start);
    second = stoi(str.substr(start, end));

    cout << "second: " << second << endl;

    start = end + 1;
    end = str.find(',', start);
    third = stod(str.substr(start, end));
    cout << "third: " << third << endl;

    start = end + 1;
    end = str.find(',', start);
    fourth = str.substr(start, end);
    cout << "fourth: " << fourth << endl;

    end = str.find(',', start);
    if (end == std::string::npos) {
        cout << "Not Found" << endl;
    } else {
        cout << "end: " << end << endl;
    }
#endif
#ifdef ex3
    size_t start{};
    size_t end{};
    int count = 0;

    do {
        count++;
        start = end != 0 ? end + 1 : 0;
        end = str.find(',', start);
        // cout << "start: " << start << endl;
        // cout << "end: " << end << endl;
        string temp = str.substr(start, (end - start));
        cout << count << ": " << temp << endl;
    } while (end != std::string::npos);

#endif
#ifdef ex4
    vector<Movie> m {
        {"The Pokemon Movie", "Anime", 120},
        {"Space Jam", "Sports Cartoon", 110},
        {"The Lion King (not live action)", "Cartoon", 130}
    };

    // Task 1 - Tell me which movie has the longest title
    // Decide what algo to use first

    // for_each
    Movie longest{"Long", "Sum", 10};
    for_each(m.begin(), m.end(), [&longest](const Movie& m) mutable {
        // what do in loop
        if (m.title.length() > longest.title.length()) {
            longest = m;
        }
    });

    cout << longest.title << endl;

    // max_element
    Movie temp = *max_element(m.begin(), m.end(), [](const Movie a, const Movie b) {
        return a.title.length() < b.title.length();
    });
    cout << temp.title << endl;

    // Task 2 -

#endif
#ifdef ex5
    ifstream fin2("words.txt");
    string f, s{};
    fin2 >> f >> s;
    cout << f << " : " << s << endl;
#endif
}