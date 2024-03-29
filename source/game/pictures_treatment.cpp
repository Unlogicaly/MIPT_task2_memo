#include "pictures_treatment.h"
#include "editting_files.h"
#include <fstream>

using std::string;

string get_pic(const string &_name, int size_h, int size_w)
{
    string name = split(_name, '\\').back();
    if (split(name, '.').size() == 1)
        name += ".gif";

    auto init_path = source + "pic\\" + name;

    if (!check_file(init_path))
    {
        std::cerr << "can't open image '" << name << "'";
        exit(-1);
    }

    auto final_path = game + "temp\\pic\\" + name;

    if (!check_file(final_path))
    {
        auto input_file = game + "temp\\im_create.in";
        std::ofstream os{input_file};
        os << init_path << std::endl
           << final_path << std::endl
           << std::to_string(size_h) << std::endl
           << std::to_string(size_w) << std::endl;
        std::system((game + "resize_image.py < " + input_file).c_str());
        del(input_file);
    }
    return final_path;
}
