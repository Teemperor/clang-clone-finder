#include <fstream>
#include <iostream>
#include "InterProcessArgs.h"
#include "CCXXEnvOverwriter.h"
#include "FakeCCListener.h"


int main(int argc, char **argv) {

    std::string fakeccPath = argv[0] + std::string("-fakecc");

    CCXXEnvOverwriter ccxxEnvOverwriter(fakeccPath);

    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    std::stringstream command;

    for (std::size_t i = 1; i < args.size(); i++) {
        command << "\"" << argv[i] << "\" ";
    }


    FakeCCListener listener;

    std::cout << "Running  '" << command.str() << "'" << std::endl;

    FILE* childProcess = popen(command.str().c_str(), "r");

    if (childProcess == NULL) {
        std::cerr << "error with popen\n";
        return 1;
    }

    /*
    char c;
    do {
        c = (char) fgetc(childProcess);
        std::cout << c;
    } while (c != EOF);
    */

    listener.run();


    std::cout << "finished" << std::endl;

    pclose(childProcess);

#if false
    Twine fileName = argv[i];
    std::string source = getFileContents(argv[i]);

    std::shared_ptr<ASTUnit> ast = clang::tooling::buildASTFromCode(source, fileName);

    FindNamedClassVisitor visitor(&ast->getASTContext());
    visitor.TraverseTranslationUnitDecl(ast->getASTContext().getTranslationUnitDecl());
#endif
}