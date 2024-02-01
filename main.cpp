#include "src/interpreter/Interpreter.h"

int main() {
    const std::string file_path = "../examples/control_flow.peechu";
    interpreter::Run(file_path);
}