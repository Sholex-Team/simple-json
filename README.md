<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<br />
<p align="center">
    <h2 align="center">Simple JSON</h2>
    <p align="center">
        <b>A small, simple and fast JSON library</b>
        <br />
        <a href="https://doc.sholex.team/simple-json/"><strong>Explore the docs »</strong></a>
        <br />
        <a href="https://github.com/Sholex-Team/simple-json/issues">Report Bug</a>
        ·
        <a href="https://github.com/Sholex-Team/simple-json/issues">Request Feature</a>
        ·
        <a href="https://github.com/Sholex-Team/simple-json/releases">Releases</a>
    </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a>
      <ul>
        <li><a href="#creating-json-objects">Creating JSON objects</a></li>
        <li><a href="#conversions-and-assignments">Conversion and Assignments</a></li>
        <li><a href="#data-access">Data Access</a></li>
        <li><a href="#range-based-iteration">Range based iteration</a></li>
        <li><a href="#using-iterators">Using iterators</a></li>
        <li><a href="#using-reverse-iterators">Using reverse iterators</a></li>
        <li><a href="#serializing-&-deserializing-using-strings">Serializing & Deserializing using strings</a></li>
        <li><a href="#serializing-&-deserializing-using-file-path">Serializing & Deserializing using file path</a></li>
        <li>
            <a href="#creating-json-patches-from-object-differences">Creating JSON Patches from object differences</a>
        </li>
        <li><a href="#creating-json-patches-from-strings">Creating JSON Patches from strings</a></li>
        <li><a href="#applying-merge-patches">Applying Merge Patches</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
Nothing special, a simple, fast and small JSON library with many interesting features.

Here are some features :
- **There is NO Dependency !**
  

- **STL-like data access and usage**
  

- **Memory efficiency** : Each JSON object has an overhead of one pointer (the maximal size of a union) and one 
  enumeration element (1 byte). 
  The default generalization uses the following C++ data 
  types: `std::string` for strings, `long int` or `double` for numbers, `std::map` for objects, `std::vector`
  for arrays, and `bool` for Booleans. 
  

- **Intuitive syntax** : We tried our best to provide a first class data type like syntax that makes creating and
using Json objects almost as easy as dictionaries in Python or objects in JS, using
  C++ operator overloading and easy to use methods.

Check out the [Documentation](https://doc.sholex.team/simple-json/) for more information.

<!-- GETTING STARTED -->
## Getting Started
All you need to do is installing the Simple JSON as a shared library or use it directly as a sub-project in your CMake
project.
## Prerequisites

There isn't much here, install CMake and you are good to go !
* CMake >= 3.16

## Installation
### Installing using PPA
1. Add the PPA to your PC
    ```sh
    sudo add-apt-repository ppa:sholex-team/simple-json
    sudo apt-get update
    ```
2. Install the library
    ```sh
    sudo apt-get install simple-json
    ```
3. Link the shared library to your project
   ```cmake
   find_package(simple-json 0.1.0 REQUIRED)
   
   target_link_libraries(${PROJECT_NAME} simple-json)
   ```
### Installing using package binary

1. Download one of the binary packages 
   ([Releases](https://github.com/Sholex-Team/simple-json/releases)).
2. Install the binary using a package manager
   ```sh
   sudo dpkg -i simple-json-0.1.0.deb
   ```
3. Link the shared library to your project
   ```cmake
   find_package(simple-json 0.1.0 REQUIRED)
   
   target_link_libraries(${PROJECT_NAME} simple-json)
   ```

### Installing using CMake

1. Clone the project
   ```shell
   git clone https://github.com/Sholex-Team/simple-json
   cd simple-json
   ```
2. Create a build directory
   ```shell
   mkdir cmake-build-release
   ```
3. Create cmake build files
   ```shell
   cmake ..
   ```
4. Build and install the project
   ```shell
   cmake --build .
   cmake --install .
   ```

### Using as a CMake embedded project

1. Clone the project inside your project
   ```shell
   cd /path/to/your/projects/third_parties/
   git clone https://github.com/Sholex-Team/simple-json
   ```
2. Add simple-json as a sub-directory in your main `CMakeLists.txt`
   ```cmake
   add_subdirectory(/path/to/your/projects/third_parties/simple-json)
   ```
3. Link the library to your project
   ```cmake
   target_link_libraries(${PROJECT_NAME} simple-json)
   ```

<!-- USAGE EXAMPLES -->
## Usage
Here are some examples of library usage 👇

### Creating JSON objects
```c++
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    Json array {1, 2, 3};
    Json json_object {{"foo"_json_key, "bar"}, {"key"_json_key, 10}};
    Json both {
            {"array"_json_key, {1, 2, 3, {
                {"first_key"_json_key, true}, {"second_key"_json_key, {10.5, true, nullptr}}}
            }},
            {"json_object"_json_key, {{{"second_inner_key"_json_key}, 10.5}}}
    };
    return 0;
}
```

### Conversions and Assignments
```c++
#include "simple_json.h"
#include <iostream>

using namespace simple_json::types;

void read_json(const Json & target_json) {
    std::cout << target_json << std::endl;
}

int main() {
    Json json {1, 2, 3};

    // Explicit Conversion
    long int second_number {json.at(1)};
    double third_number {static_cast<double>(json.at(2))};

    // Converting an Array to std::string is impossible !
    try {
        static_cast<std::string>(json);
    } catch (const exceptions::BadConversion & error) {
        std::cout << error.what() << std::endl;
    }

    // Implicit Conversion
    read_json(10);

    // Assignments
    json = 10;
    json += 10;
    Json second_json = json - 5;
    return 0;
}
```

### Data Access
```c++
#include "simple_json.h"
#include <iostream>
  
using namespace simple_json::types;

int main() {
    Json json {
        {"array"_json_key, {1, 2, 3, {
            {"first_key"_json_key, true}, {"second_key"_json_key, {10.5, true, nullptr}}}
        }},
        {"json_object"_json_key, {{{"second_inner_key"_json_key}, 10.5}}}
    };
    
    // Using indexes and keys
    std::cout << json.at("array"_json_key)[3]["second_key"] << std::endl;
    
    // Getting a reference to inner values
    Array & inner_array {json.at("array").get_array()};
    inner_array.push_back(10);
    double & inner_double {json.at("json_object").at("second_inner_key").get_double()};
    inner_double *= 2;
    
    // Output must be 21
    std::cout << json.at("json_object").at("second_inner_key") << std::endl;
    return 0;
}
```

### Range based iteration
```c++
#include "simple_json.h"
#include <iostream>
  
using namespace simple_json::types;

int main() {
    Json json {
        {"array"_json_key, {1, 2, 3, {
            {"first_key"_json_key, true}, {"second_key"_json_key, {10.5, true, nullptr}}}
        }},
        {"json_object"_json_key, {{{"second_inner_key"_json_key}, 10.5}}}
    };
    for (const pair_type & pair: json.items()) {
        std::cout << "Key : " << pair.first << std::endl;
        std::cout << "Value : " << pair.second << std::endl;
    }
    for (const Json & item: json.at("array"_json_key)) {
        std::cout << item << std::endl;
    }
    return 0;
}
```

### Using iterators
```c++
#include "simple_json.h"
#include <iostream>
  
using namespace simple_json::types;

int main() {
    Json json {
        {"array"_json_key, {1, 2, 3, {
            {"first_key"_json_key, true}, {"second_key"_json_key, {10.5, true, nullptr}}}
        }},
        {"json_object"_json_key, {{{"second_inner_key"_json_key}, 10.5}}}
    };
    for (Json::iterator it = json.begin(); it != json.end(); ++it) {
        std::cout << "Key : " << it.key() << std::endl;
        std::cout << "Value : " << it.value() << std::endl;
    }
    for (Json::const_iterator it = json.at("array").cbegin(); it != json.at("array").cend(); ++it) {
        std::cout << "Value : " << * it << std::endl;
    }
    return 0;
}
```

### Using reverse iterators
```c++
#include "simple_json.h"
#include <iostream>

using namespace simple_json::types;

int main() {
    Json json {
      {"array"_json_key, {1, 2, 3, {
          {"first_key"_json_key, true}, {"second_key"_json_key, {10.5, true, nullptr}}}
      }},
      {"json_object"_json_key, {{{"second_inner_key"_json_key}, 10.5}}}
    };
    for (Json::reverse_iterator it = json.rbegin(); it != json.rend(); ++it) {
      std::cout << "Key : " << it.key() << std::endl;
      std::cout << "Value : " << it.value() << std::endl;
    }
    for (Json::const_reverse_iterator it = json.at("array").crbegin(); it != json.at("array").crend(); ++it) {
      std::cout << "Value : " << * it << std::endl;
    }
    return 0;
}
```

### Serializing & Deserializing using strings
```c++
#include <iostream>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::deserializer;
using namespace ::serializer;

int main() {
    const Json json(loads(R"({"foo": "bar", "int_value": 10, "array": [1, 12, true, null]})"));
    const std::string serialized_json {dumps(json)};
  
    std::cout << json << std::endl;
    std::cout << serialized_json << std::endl;
    return 0;
}
```
### Serializer & Deserializing using file path
```c++
#include <iostream>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::deserializer;
using namespace ::serializer;

int main() {
    Json json(DataType::unknown);
    try {
        json = load("serialized.json");
    } catch (const deserializer::exceptions::ReadingFromFileException & error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    json = {1, 2, 3};
    try {
        dump(json, "new_serialized.json");
    } catch (const serializer::exceptions::WritingToFileException & error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}

```

### Using JSON Pointers
```c++
#include "simple_json.h"
#include <iostream>

int main() {
    Json src {{"array"_json_key, {1, 2, {{"inner_key"_json_key, 10}}}}, {"foo"_json_key, "bar"}};
    
    // Using JSON Pointer to access inner_key
    Json inner_value(src.at("/array/2/inner_key"_json_ptr));

    std::cout << inner_value << std::endl; // Output is 10
    return 0;
}
```

### Creating JSON Patches from object differences
```c++
#include <iostream>
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    const Json src {1, 2, 3, 4};
    Json dst {9, 2, 3, 7};
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    patch.apply(dst);
    std::cout << std::boolalpha << "Test : " << (src == dst) << std::endl;
    return 0;
}
```

### Creating JSON Patches from strings
```c++
#include <iostream>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::deserializer;
int main() {
    Json src {{"array"_json_key, {1, 2, 3}}, {"foo"_json_key, "bar"}};
    Json patch_data(loads(R"([
            {"op": "remove", "path": "/array/0"},
            {"op": "test", "path": "/foo", "value": "bar"},
            {"op": "add", "path": "/array/2", "value": 5}
    ])"));
    JsonPatch patch {patch_data};
    try {
        patch.apply(src);
    } catch (const types::exceptions::FailedTest & error) {
        std::cout << error.what() << std::endl;
    }
    std::cout << src << std::endl;
    return 0;
}
```

### Applying Merge Patches
```c++
#include "simple_json.h"
#include <iostream>

using namespace simple_json::types;

int main() {
    // Creating source JSON
    Json json(loads(R"({
      "a": "b",
      "c": {
        "d": "e",
        "f": "g"
      }
    })"));
    
    // Creating merge patch
    Json patch(loads(R"({
      "a":"z",
      "c": {
        "f": null
      }
    })"));
    
    // Applying the Merge Patch
    json.merge_patch(patch);
    std::cout << json << std::endl;
}
```

_For more examples, please refer to the [Documentation](https://doc.sholex.team/simple-json/)_

<!-- CONTRIBUTING -->
## Contributing
There isn't any kind of rules for contributing to this project, if anything useful comes to your mind please feel free
to share it with us 👇

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License
Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact
NitroZeus - [@detnawitna](https://t.me/detnawitna)

RezFD - [@RezFD](https://t.me/RezFD)

Project Link: [https://github.com/Sholex-Team/simple-json](https://github.com/Sholex-Team/simple-json)
