FROM ubuntu:16.04

RUN apt-get update && apt install -y \
    cmake \
    g++ \
    libgoogle-glog-dev \
    libgtest-dev \
    scons && \
    cd /usr/src/gtest && \
    cmake -DBUILD_SHARED_LIBS=ON . && \
    make && \
    mv libg* /usr/lib/ && \
    apt-get remove -y cmake && \
    apt-get autoremove -y
