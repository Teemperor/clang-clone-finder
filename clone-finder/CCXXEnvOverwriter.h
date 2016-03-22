#ifndef STANDALONE_CCXXENVOVERWRITER_H
#define STANDALONE_CCXXENVOVERWRITER_H

#include <string>
#include <cstdlib>

class CCXXEnvOverwriter {

    std::string originalCCValue;
    std::string originalCXXValue;
public:
    CCXXEnvOverwriter(const std::string& overwrite) {
        if (std::getenv("CC"))
            originalCCValue = getenv("CC");
        if (std::getenv("CXX"))
            originalCXXValue = getenv("CXX");

        setenv("CC", overwrite.c_str(), 1);
        setenv("CXX", overwrite.c_str(), 1);
    }
    ~CCXXEnvOverwriter() {
        setenv("CC", originalCCValue.c_str(), 1);
        setenv("CXX", originalCXXValue.c_str(), 1);
    }
};

#endif //STANDALONE_CCXXENVOVERWRITER_H
