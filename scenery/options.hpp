#ifndef OPTIONS_HPP
#define OPTIONS_HPP


struct Options{
    Options()
        : help()
    {}

    bool help;
    bool verbose;
    std::string configfile;

    std::string name;
    int screen_width;
    int screen_height;
    std::string map;
};

#endif
