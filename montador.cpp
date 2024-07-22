#include "./src/assembler/flow/assembler_factory.hpp"
#include "./src/utils/logger.hpp"
#include "./src/exceptions/exceptions.hpp"

#include <filesystem>
#include <iostream>

using namespace std;
using namespace basilar::assembler::flow;
using namespace basilar::exceptions;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " [-p|-o] INPUT_FILE_PATH" << endl;
        return 1;
    }

    auto option = string(argv[1]);
    if (option != "-p" && option != "-o") {
        cout << "Invalid option: " << option << endl;
        return 1;
    }

    auto source_file_path = argv[2];
    auto extension = option == "-p" ? ".pre" : ".obj";
    auto output_file_path = filesystem::path(source_file_path).replace_extension(extension).string();

    LOG_DEBUG("Starting assembler...");
    LOG_INFO("Source file path: " + string(source_file_path));
    LOG_INFO("Output file path: " + string(output_file_path));

    AssemblerFlow flow;
    if (option == "-p") {
        LOG_DEBUG("Using preprocessor flow");
        flow = AssemblerFactory::create_preprocessor_flow(source_file_path, output_file_path);
    } else {
        LOG_DEBUG("Using assembler flow");
        flow = AssemblerFactory::create_assembler_flow(source_file_path, output_file_path);
    }
    
    try {
        flow.run();
    } catch (const semantic_exception& e) {
        cout << string(e.get_message()) << endl;
        return 1;
    } catch (const lexycal_exception& e) {
        cout << string(e.get_message()) << endl;
        return 1;
    } catch (const ParsingException& e) {
        cout << string(e.get_message()) << endl;
        return 1;
    } catch (const exception& e) {
        LOG_ERROR("Fatal error: " + string(e.what()));
        return 1;
    }
    
    return 0;
}