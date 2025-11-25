# IKOS is developed by NASA to analyze code
# See this link for more info: 
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update --yes
RUN apt-get install --yes \
		 git gcc g++ cmake libgmp-dev libboost-dev libboost-filesystem-dev \
		 libboost-thread-dev libboost-test-dev \
		 libsqlite3-dev libtbb-dev libz-dev libedit-dev \
		 python3 python3-pip \
		 llvm-14 llvm-14-dev llvm-14-tools clang-14


RUN git clone https://github.com/NASA-SW-VnV/ikos.git /ikos
WORKDIR /ikos
RUN git checkout v3.2

RUN mkdir /ikos/build
WORKDIR /ikos/build

RUN cmake \
		 -DCMAKE_INSTALL_PREFIX="/opt/ikos" \
		 -DLLVM_CONFIG_EXECUTABLE="/usr/lib/llvm-14/bin/llvm-config" \
		 ..

RUN make -j4
RUN make install

RUN chmod +x /opt/ikos/bin/ikos
RUN /opt/ikos/bin/ikos --version

CMD ["/opt/ikos/bin/ikos"]
