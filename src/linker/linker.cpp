#include "linker.hpp"
#include "object_reader/object_reader.hpp"
#include "../utils/logger.hpp"

#include <string>
#include <fstream>
using namespace std;

namespace basilar::linker {

string read_file(string file) {
    ifstream file_stream(file);
    string file_content((istreambuf_iterator<char>(file_stream)), istreambuf_iterator<char>());
    return file_content;
}

ObjectsBuilder Linker::link() {
    LOG_DEBUG("Linking files: " + __file1 + " and " + __file2);
    auto file_content1 = read_file(__file1);
    auto file_content2 = read_file(__file2);

    LOG_DEBUG("Read files successfully. Creating object readers.");
    ObjectsReader reader1(file_content1);
    ObjectsReader reader2(file_content2);

    LOG_DEBUG("Reading objects from files.");
    ObjectsBuilder builder1 = reader1.read();
    ObjectsBuilder builder2 = reader2.read();

    LOG_DEBUG("Linking objects.");
    builder1.link(builder2);

    LOG_DEBUG("Linking finished.");
    return builder1;
}

} // namespace basilar::linker