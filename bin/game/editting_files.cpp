#include "editting_files.h"
#include <fstream>
#include <sstream>

using std::string;

void del(const string &path)
{
    std::remove(path.c_str());
}

void read_directory(const std::string &name, std::vector<string> &v)
{
    string buffer = "list_dir_temp.out";
    string command = "dir /b " + name + " > " + buffer;

    system(command.c_str());

    std::ifstream is{buffer};

    string s;
    while (!is.eof())
    {
        getline(is, s);
        v.push_back(s);
    }

    del(buffer);
}

void clear()
{
    std::vector<std::string> files;
    read_directory(game + "temp\\pic", files);

    for (auto &file : files)
    {
        if (!file.empty())
            del(get_pic(file));
    }
}

bool check_file(const std::string &path)
{
    std::ifstream is{path};
    return is.good();
}

void cl(std::vector<string> &src)
{
    for (auto i = 0; i < src.size(); ++i)
        if (src[i].empty())
        {
            src.erase(src.begin() + i, src.begin() + i + 1);
            --i;
        }
}

void get_names(std::vector<std::string> &names)
{
    std::ifstream is(game + "source\\pictures.txt");
    string s;
    while (is >> s)
        names.push_back(s);
}
