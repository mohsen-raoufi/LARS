# Setup Instructions

## 1. Install Ubuntu 20.04 LTS

## 2. Update Everything
- Run the following commands in the terminal:
    ```
    sudo apt-get update && sudo apt-get upgrade
    ```
- Run the Software Updater.

## 3. Install Latest Qt
- Use the command:
    ```
    sudo apt-get install qtcreator
    ```

## 4. Install Git
- Install Git with:
    ```
    sudo apt-get install git
    ```

---

# GPU Computing Setup

## 5. Install Nvidia Driver
- **Purge everything Nvidia related:**
    ```
    sudo apt purge nvidia-*
    ```
- **Add repository:**
    ```
    sudo add-apt-repository ppa:graphics/ppa
    ```
- **Update:**
    ```
    sudo apt-get update
    ```
- **Install driver:**
    ```
    sudo apt-get install nvidia-470
    ```

## 6. Reboot

## 7. Install OpenCV
- **Download OpenCV 4.5.5 from:** [https://github.com/opencv/opencv/archive/refs/tags/4.5.5.tar.gz](https://github.com/opencv/opencv/archive/refs/tags/4.5.5.tar.gz)
- **Create folder for LARS and cd:**
    ```
    mkdir ~/LARS_project && cd ~/LARS_project
    ```
- **Untar downloaded OpenCV:**
    ```
    tar -xcf ~/Downloads/opencv-4.5.5.tar.gz opencv-4.5.5
    ```
- **Download OpenCV contrib tools:**
    ```
    git clone https://github.com/opencv/opencv_contrib.git
    ```

### Install Prerequisites:

- Install necessary packages using the following commands:
    ```
    sudo apt install --assume-yes build-essential cmake git pkg-config unzip ffmpeg qtbase5-dev python-dev python3-dev python-numpy python3-numpy
    sudo apt install libhdf5-dev
    sudo apt install --assume-yes libgtk-3-dev libdc1394-22 libdc1394-22-dev libjpeg-dev libpng-dev libtiff5-dev
    sudo apt install --assume-yes libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
    sudo apt install --assume-yes libv4l-dev libtbb-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev
    sudo apt install --assume-yes libvorbis-dev libxvidcore-dev v4l-utils
    ```

### Configure CMake:

- Navigate and configure using cmake with the following steps:
    ```
    cd ~/LARS_project/opencv-4.5.5
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_CUDA=ON -D WITH_CUBLAS=ON -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -DCUDA_NVCC_FLAGS="-D_FORCE_INLINES" -DOPENCV_EXTRA_MODULES_PATH=~/ARK_project/opencv_contrib/modules -DCMAKE_SHARED_LINKER_FLAGS='-latomic' ..
    ```

#### *Optional:* If there are errors in compilation, use an older version of gcc and g++:

- Install different versions and update system alternatives with the following commands:
    ```
    sudo apt -y install gcc-7 g++-7 gcc-8 g++-8 gcc-9 g++-9
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 7
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 8
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 7
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 8
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9
    ```
- Switch to gcc-7 and g++-7 as needed.

### Build and Install OpenCV:

- Compile and install OpenCV with the commands:
    ```
    make -j $(($(nproc) + 1))
    sudo make install
    ```

## 8. Compile LARS
- Follow these steps to compile and set up LARS:
    - **Navigate to the LARS project directory:**
        ```
        cd ~/LARS_project
        ```
    - **Clone the LARS Code:**
        ```
        git clone https://github.com/mohsen-raoufi/LARS.git
        ```
    - **Open QT Creator and the project:**
        - Open QT creator.
        - Open project and select `CMakeList.txt` (or `.pro` file) in the cloned directory of LARS.
        - Build and run.

## 9. Enjoy
