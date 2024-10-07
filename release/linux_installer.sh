#!/bin/bash

# COLORS :
RED='\033[0;31m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m'

# KEYWORDS :
ERROR="${RED}[ERROR]:${NC}"
WARNING="${YELLOW}[WARNING]:${NC}"
INFO="${BLUE}[INFO]:${NC}"
SUCCESS="${GREEN}[SUCCESS]${NC}"

launch_message() {

    echo -e "${CYAN}########################################################################${NC}"
    echo -e "${CYAN}#${NC}                   ${GREEN}WELCOME TO RTYPE LINUX INSTALLER${NC}                   ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}                                                                      ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}                        ${BLUE}PROJECT DONE BY:${NC}                              ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @Adam Lesage : https://github.com/AdamLesage              ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @rchevallier1234 : https://github.com/rchevallier1234     ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @BxptisteM : https://github.com/BxptisteM                 ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @mathieu-MZ : https://github.com/mathieu-MZ               ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @Victorhrst : https://github.com/Victorhrst               ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}          - @Klayni : https://github.com/Klayni                       ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}                                                                      ${CYAN}#${NC}"
    echo -e "${CYAN}#${NC}                    ${BLUE}PROJECT DONE FOR:${NC} EPITECH PROJECT                 ${CYAN}#${NC}"
    echo -e "${CYAN}########################################################################${NC}"
    echo ""
}

message() {
    local keyword=$1
    local message=$2

    if [ -z "$keyword" ] || [ -z "$message" ]; then
        echo -e "${ERROR} message() function requires two arguments."
        exit 84
    fi

    echo -e "${keyword} ${message}"
}

progress_bar() {
    local duration=5
    already_done() { for ((done=0; done<$elapsed; done++)); do printf "█"; done }
    remaining() { for ((remain=$elapsed; remain<$duration; remain++)); do printf " "; done }
    percentage() { printf "| %s%%" $(( ($elapsed*100)/$duration )); }

    for ((elapsed=1; elapsed<=$duration; elapsed++))
    do
        already_done; remaining; percentage
        sleep 1
        printf "\r"
    done
    printf "\n"
}

is_package_installed() {
    case "$install_package_manager" in
        "apt")
            dpkg -l | grep -q "$1"  > /dev/null 2>&1
        ;;
        "dnf")
            dnf list installed "$1" > /dev/null 2>&1
        ;;
        "yum")
            yum list installed "$1" > /dev/null 2>&1
        ;;
        "pacman")
            pacman -Qs "$1" > /dev/null 2>&1
        ;;
        "apk")
            apk info | grep -q "$1"
        ;;
    esac
}

get_linux_distribution() {
    message "$INFO" "This script will install the required packages for the RType project."
    message "$INFO" "Do you want to continue ? (y/n)"
    read -r answer

    if [ "$answer" != "y" ]; then
        message "$WARNING" "Installation aborted, exiting..."
        exit 84
    fi

    message "$INFO" "Detecting distribution..."
    if [ ! -f /etc/os-release ]; then
        message "$ERROR" "Unable to detect distribution (/etc/os-release not found)"
        exit 84
    fi

    . /etc/os-release
    distribution=$ID

    case "$distribution" in
        "debian" | "ubuntu" | "devuan")
            message "$INFO" "Detected distribution: $distribution, use of apt package manager."
            install_package_manager="apt"
        ;;
        "fedora")
            message "$INFO" "Detected distribution: $distribution, use of dnf package manager."
            install_package_manager="dnf"
        ;;
        "centos" | "rhel")
            message "$INFO" "Detected distribution: $distribution, use of yum package manager."
            install_package_manager="yum"
        ;;
        "arch")
            message "$INFO" "Detected distribution: $distribution, use of pacman package manager."
            install_package_manager="pacman"
        ;;
        "alpine")
            message "$INFO" "Detected distribution: $distribution, use of apk package manager."
            install_package_manager="apk"
        ;;
        *)
            message "$ERROR" "Unsupported distribution: $distribution"
            exit 84
        ;;
    esac
}

install_utils() {
    message "$INFO" "Checking if required packages (g++, make, git, autoconf, libtool, curl, pkg-config, libx11-dev, libxrandr-dev, libxcursor-dev, libxi-dev, libudev-dev, libgl1-mesa-dev) are installed..."

    if is_package_installed "g++" && is_package_installed "make" && is_package_installed "git" && \
       is_package_installed "autoconf" && is_package_installed "libtool" && is_package_installed "curl" && \
       is_package_installed "pkg-config" && is_package_installed "libx11-dev" && is_package_installed "libxrandr-dev" && \
       is_package_installed "libxcursor-dev" && is_package_installed "libxi-dev" && is_package_installed "libudev-dev" && \
       is_package_installed "libgl1-mesa-dev"; then
        message "$SUCCESS" "All required packages (g++, make, git, autoconf, libtool, curl, pkg-config, libx11-dev, libxrandr-dev, libxcursor-dev, libxi-dev, libudev-dev, libgl1-mesa-dev) are already installed."
        return 0
    fi

    message "$INFO" "The following packages will be installed: g++, make, git, autoconf, libtool, curl, pkg-config, libx11-dev, libxrandr-dev, libxcursor-dev, libxi-dev, libudev-dev, libgl1-mesa-dev."
    message "$INFO" "Do you want to continue? (y/n)"
    read -r answer

    if [ "$answer" != "y" ]; then
        message "$WARNING" "Installation aborted, exiting..."
        exit 84
    fi

    message "$INFO" "You may be asked for your password to proceed with the installation."

    case "$install_package_manager" in
        "apt")
            sudo apt update > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to update package lists with apt."
                exit 84
            fi
            sudo apt install -y g++ build-essential git autoconf libtool curl pkg-config \
                libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install required packages with apt."
                exit 84
            fi
        ;;
        "dnf")
            sudo dnf install -y gcc-c++ make git autoconf libtool curl pkg-config \
                libX11-devel libXrandr-devel libXcursor-devel libXi-devel libudev-devel mesa-libGL-devel > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install required packages with dnf."
                exit 84
            fi
        ;;
        "yum")
            sudo yum install -y gcc-c++ make git autoconf libtool curl pkg-config \
                libX11-devel libXrandr-devel libXcursor-devel libXi-devel libudev-devel mesa-libGL-devel > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install required packages with yum."
                exit 84
            fi
        ;;
        "pacman")
            sudo pacman -Syu --noconfirm gcc make git autoconf libtool curl pkg-config \
                libx11 libxrandr libxcursor libxi libudev mesa > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install required packages with pacman."
                exit 84
            fi
        ;;
        "apk")
            sudo apk add --no-cache g++ make git autoconf libtool curl pkg-config \
                libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev mesa-dev > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install required packages with apk."
                exit 84
            fi
        ;;
        *)
            message "$ERROR" "Unsupported package manager: $install_package_manager"
            exit 84
        ;;
    esac

    message "$INFO" "Installation in progress..."
    progress_bar

    message "$SUCCESS" "All required packages (g++, make, git, autoconf, libtool, curl, pkg-config, libx11-dev, libxrandr-dev, libxcursor-dev, libxi-dev, libudev-dev, libgl1-mesa-dev) installed successfully."
}

install_make_cmake() {
    message "$INFO" "Checking if Make and CMake are already installed..."

    is_package_installed() {
        case "$install_package_manager" in
            "apt")
                dpkg -l | grep -q "$1"  > /dev/null 2>&1
            ;;
            "dnf")
                dnf list installed "$1" > /dev/null 2>&1
            ;;
            "yum")
                yum list installed "$1" > /dev/null 2>&1
            ;;
            "pacman")
                pacman -Qs "$1" > /dev/null 2>&1
            ;;
            "apk")
                apk info | grep -q "$1"
            ;;
        esac
    }

    if is_package_installed "make" && is_package_installed "cmake"; then
        message "$SUCCESS" "Make and CMake are already installed."
        return 0
    fi

    message "$INFO" "Installing Make and CMake..."
    message "$INFO" "Do you want to continue ? (y/n)"
    read -r answer

    if [ "$answer" != "y" ]; then
        message "$WARNING" "Installation aborted, exiting..."
        exit 84
    fi

    message "$INFO" "You may be asked for your password to proceed with the installation."

    case "$install_package_manager" in
        "apt")
            sudo apt update > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to update package lists with apt."
                exit 84
            fi
            sudo apt install -y make cmake > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install Make and CMake with apt."
                exit 84
            fi
        ;;
        "dnf")
            sudo dnf install -y make cmake > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install Make and CMake with dnf."
                exit 84
            fi
        ;;
        "yum")
            sudo yum install -y make cmake > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install Make and CMake with yum."
                exit 84
            fi
        ;;
        "pacman")
            sudo pacman -Syu --noconfirm make cmake > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install Make and CMake with pacman."
                exit 84
            fi
        ;;
        "apk")
            sudo apk add --no-cache make cmake > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                message "$ERROR" "Failed to install Make and CMake with apk."
                exit 84
            fi
        ;;
    esac

    message "$INFO" "Installation in progress..."
    progress_bar

    message "$SUCCESS" "Make and CMake installed successfully."
}

install_package_manager() {
    VCPKG_ROOT="$HOME/vcpkg"
    export VCPKG_ROOT
    source ~/.bashrc

    if [ -d "$VCPKG_ROOT" ]; then
        message "$SUCCESS" "vcpkg is already installed in $VCPKG_ROOT."
        return 0
    fi

    message "$INFO" "Downloading vcpkg via git clone..."
    mkdir -p "$VCPKG_ROOT"

    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT"  > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to clone vcpkg repository."
        exit 84
    fi

    message "$INFO" "Building vcpkg..."
    "$VCPKG_ROOT/bootstrap-vcpkg.sh" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to build vcpkg."
        exit 84
    fi

    message "$INFO" "Configuring environment variable VCPKG_ROOT..."
    export VCPKG_ROOT="$VCPKG_ROOT"

    if ! grep -q "VCPKG_ROOT" "$HOME/.bashrc"; then
        echo "export VCPKG_ROOT=$VCPKG_ROOT" >> "$HOME/.bashrc"
        echo "export PATH=\$VCPKG_ROOT:\$PATH" >> "$HOME/.bashrc"
        message "$SUCCESS" "VCPKG_ROOT configured and added to .bashrc."
    fi

    message "$SUCCESS" "vcpkg installed successfully at $VCPKG_ROOT."
}

install_dependencies() {
    if [ -z "$VCPKG_ROOT" ] || [ ! -d "$VCPKG_ROOT" ]; then
        message "$ERROR" "vcpkg is not installed or VCPKG_ROOT is not set."
        return 84
    fi

    message "$INFO" "Installing system dependencies for SFML..."

    case "$install_package_manager" in
        "apt")
            sudo apt update > /dev/null 2>&1
            sudo apt upgrade -y > /dev/null 2>&1
            sudo apt install -y build-essential libasound2-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev > /dev/null 2>&1
        ;;
        "dnf")
            sudo dnf groupinstall "Development Tools" "Development Libraries" > /dev/null 2>&1
            sudo dnf install -y alsa-lib-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel > /dev/null 2>&1
        ;;
        "pacman")
            sudo pacman -Syu --needed base-devel alsa-lib libx11 libxrandr libxinerama libxcursor libxi > /dev/null 2>&1
        ;;
    esac

    message "$INFO" "Installing dependencies (SFML, Boost, libconfig) with vcpkg..."

    "$VCPKG_ROOT/vcpkg" install alsa > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to install ALSA."
        return 84
    fi

    "$VCPKG_ROOT/vcpkg" install sfml > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to install SFML."
        return 84
    fi

    message "$INFO" "Installing Boost..."
    "$VCPKG_ROOT/vcpkg" install boost-asio > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to install Boost."
        return 84
    fi

    message "$INFO" "Installing libconfig..."
    "$VCPKG_ROOT/vcpkg" install libconfig > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        message "$ERROR" "Failed to install libconfig."
        return 84
    fi

    message "$SUCCESS" "Dependencies (SFML, Boost, libconfig) installed successfully."
}

main () {
    launch_message
    message "$INFO" "Starting installation..."
    get_linux_distribution
    install_utils
    install_make_cmake
    install_package_manager
    source ~/.bashrc
    install_dependencies
    message "$INFO" "Building R-Type project..."
    cd R-Type-epitech
    make release
    sudo ln -s "$(pwd)/r-type_client" ../r-type_client
    sudo ln -s "$(pwd)/r-type_server" ../r-type_server
    cd ..
    message "$SUCCESS" "Installation completed successfully."
}

main
