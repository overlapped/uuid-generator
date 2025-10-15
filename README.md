# Building and Running

## Create build directory and build:

```bash

mkdir build
cd build
cmake ..
make
```

## Run the application:

```bash

# Run on port 8080
./uuid-generator --http-port=8080 --docroot=.

# Or with more options
./uuid-generator --http-port=8080 --docroot=. --approot=.
```

## Access the application:

Open your web browser and navigate to http://localhost:8080

### Features

- UUID Generation: Generates RFC-compliant UUID version 4 (random)
- User Interface: Clean, responsive web interface
- Copy Functionality: Users can easily copy the generated UUID from the text field
- New Generation: Button to generate a new UUID on demand
- Proper Formatting: UUIDs are displayed in the standard 8-4-4-4-12 format

### Dependencies

- C++14 compatible compiler
- CMake 3.10+
- Emweb Wt Toolkit (libwt-dev, libwthttp-dev)
- PkgConfig

## Installation on Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libwt-dev libwthttp-dev cmake pkg-config build-essential
```

The application will start a web server on the specified port (default 8080) and serve the UUID generator interface. Users can generate new UUIDs by clicking the button and copy them from the read-only text field.
