#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " INFILE OUTFILE" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream inf(std::string(argv[1]), std::ios::binary);
    std::ofstream outf(std::string(argv[2]), std::ios::binary);
    std::string line;
    while (std::getline(inf, line)) {
        std::vector<std::string> fields;
        size_t lastcm = 0;
        size_t nextcm = 0;
        while ((nextcm = line.find(",", lastcm)) != std::string::npos) {
            fields.push_back(line.substr(lastcm, nextcm-lastcm));
            lastcm = nextcm + 1;
        }
        fields.push_back(line.substr(lastcm));
        bool first = true;
        for (auto& field : fields) {
            if (!first) {
                outf << "\t";
            }
            outf << field;
            first = false;
        }
        outf << "\n";
    }
    return EXIT_SUCCESS;
}
