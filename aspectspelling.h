#include <string>

class AspectSpelling : std::exception {
    const char* what() const throw() {
        std::string s = "Spelling mistake in apsect";
        return s.c_str();
    }
};