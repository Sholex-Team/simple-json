#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json p(loads(R"([
  {
      "voters": [],
      "accept_vote": [
        405154
        ]
    }
  ])"));
    std::cout << set_indent() << p;
    return 0;
}
