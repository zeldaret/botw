FROM ubuntu:latest

MAINTAINER Léo <leo@leolam.fr>

# devkitpro/devkita64:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends apt-utils && \
    apt-get install -y --no-install-recommends sudo ca-certificates pkg-config curl wget xz-utils make git gnupg && \
    apt-get install -y --no-install-recommends gdebi-core && \
    apt-get install -y --no-install-recommends cmake && \
    apt-get install -y --no-install-recommends libncurses5 ninja-build && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/devkitPro/pacman/releases/latest/download/devkitpro-pacman.amd64.deb && \
    gdebi -n devkitpro-pacman.amd64.deb && \
    rm devkitpro-pacman.amd64.deb && \
    dkp-pacman -Scc --noconfirm

RUN dkp-pacman -Syyu --noconfirm switch-dev && \
    dkp-pacman -Scc --noconfirm

ENV DEVKITPRO=/opt/devkitpro
ENV DEVKITA64=/opt/devkitpro/devkitA64
ENV PATH=${DEVKITPRO}/tools/bin:$DEVKITA64/bin:$PATH

# BotW build

RUN wget https://releases.llvm.org/4.0.1/clang+llvm-4.0.1-x86_64-linux-gnu-debian8.tar.xz && \
    tar xf clang+llvm-4.0.1-x86_64-linux-gnu-debian8.tar.xz && \
    rm clang+llvm-4.0.1-x86_64-linux-gnu-debian8.tar.xz && \
    mv clang+llvm-4.0.1-x86_64-linux-gnu-debian8 /opt/clang-4.0.1

ENV UKING_CLANG=/opt/clang-4.0.1
