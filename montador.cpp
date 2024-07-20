#include "./src/assembler/flow/assembler_factory.hpp"
#include "./src/utils/logger.hpp"
#include <iostream>

using namespace std;
using namespace basilar::assembler::flow;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <source_file_path> <output_file_path>" << endl;
        return 1;
    }

    auto source_file_path = argv[1];
    auto output_file_path = argv[2];

    LOG_DEBUG("Starting assembler...");
    cout << "Source file path: " << source_file_path << endl;
    cout << "Output file path: " << output_file_path << endl;
    // cout << "Creating preprocessor flow..." << endl;
    // auto flow = AssemblerFactory::create_preprocessor_flow(source_file_path, output_file_path);

    // cout << "Running preprocessor flow..." << endl;
    // flow.run();

    // cout << "Preprocessor flow finished." << endl;

    cout << "Creating assembler flow..." << endl;
    auto flow = AssemblerFactory::create_assembler_flow(source_file_path, output_file_path);

    cout << "Running assembler flow..." << endl;
    flow.run();

    cout << "Assembler flow finished." << endl;

    return 0;
}