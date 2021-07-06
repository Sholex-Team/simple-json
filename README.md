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
        <a href="https://doc.sholexteam.ir/simple-json/"><strong>Explore the docs »</strong></a>
        <br />
        <a href="https://github.com/Sholex-Team/simple-json/issues">Report Bug</a>
        ·
        <a href="https://github.com/Sholex-Team/simple-json/issues">Request Feature</a>
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
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

There are many great README templates available on GitHub, however, I didn't find one that really suit my needs so I created this enhanced one. I want to create a README template so amazing that it'll be the last one you ever need -- I think this is it.

Here's why:
* Your time should be focused on creating something amazing. A project that solves a problem and helps others
* You shouldn't be doing the same tasks over and over like creating a README from scratch
* You should element DRY principles to the rest of your life :smile:

Of course, no one template will serve all projects since your needs may be different. So I'll be adding more in the near future. You may also suggest changes by forking this repo and creating a pull request or opening an issue. Thanks to all the people have have contributed to expanding this template!

A list of commonly used resources that I find helpful are listed in the acknowledgements.

<!-- GETTING STARTED -->
## Getting Started
All you need to do is installing the Simple JSON as a shared library or use it directly as a sub-project in your CMake
project.
### Prerequisites

There isn't much here, install CMake and you are good to go !
* CMake >= 3.16

### Installing using package managers

1. Download one of the binary packages ([DEB](https://bin.sholexteam.ir/simple-json/deb/simple_json-1.0.0.deb)
   , [RPM](https://bin.sholexteam.ir/simple-json/rpm/simple_json-1.0.0.rpm))
2. Install the binary using a package manager
   ```sh
   sudo dpkg -i simple_json-1.0.0.deb
   ```
3. Add the shared library to your project
   ```cmake
   find_package(simple_json 1.0.0 REQUIRED)
   
   target_link_libraries(${PROJECT_NAME} simple_json)
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

### Using as a CMake sub-project

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
   target_link_libraries(${PROJECT_NAME} simple_json)
   ```

<!-- USAGE EXAMPLES -->
## Usage
Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://doc.sholexteam.ir/simple-json/)_

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
