//일반적으로 돌리기
cd /home/fastech/Desktop/so
gcc -c EthernetInterface.c -o EthernetInterface.o
gcc -c FAS_EziMOTIONPlusE.c -o FAS_EziMOTIONPlusE.o
gcc -c Fsocket.c -o Fsocket.o
gcc -c ProtocolTest.c -o ProtocolTest.o
gcc ProtocolTest.o EthernetInterface.o FAS_EziMOTIONPlusE.o Fsocket.o -o ProtocolTest
./ProtocolTest

//CommandPosition_ActualPosition돌리기
cd /home/fastech/Desktop/so
gcc -c EthernetInterface.c -o EthernetInterface.o
gcc -c FAS_EziMOTIONPlusE.c -o FAS_EziMOTIONPlusE.o
gcc -c Fsocket.c -o Fsocket.o
gcc -c CommandPosition_ActualPosition.c -o CommandPosition_ActualPosition.o
gcc CommandPosition_ActualPosition.o EthernetInterface.o FAS_EziMOTIONPlusE.o Fsocket.o -o CommandPosition_ActualPosition
./CommandPosition_ActualPosition

//so파일 만들기 및 실행 방법:
cd /home/fastech/Desktop/so

# EthernetInterface.c, FAS_EziMOTIONPlusE.c, Fsocket.c 컴파일
gcc -c -fpic EthernetInterface.c -o EthernetInterface.o
gcc -c -fpic FAS_EziMOTIONPlusE.c -o FAS_EziMOTIONPlusE.o
gcc -c -fpic Fsocket.c -o Fsocket.o

# 공유 라이브러리 생성 (이름을 "libEziMOTION.so"로 지정)
gcc -shared -o libEziMOTION.so EthernetInterface.o FAS_EziMOTIONPlusE.o Fsocket.o

# main.c 컴파일 및 라이브러리 링크
gcc -o CommandPosition_ActualPosition CommandPosition_ActualPosition.c -L. -lEziMOTION
gcc -o ProtocolTest ProtocolTest.c -L. -lEziMOTION

#라이브러리를 시스템 디렉토리에 복사: (영구적)
sudo cp libEziMOTION.so /usr/lib
sudo ldconfig
./main

#LD_LIBRARY_PATH 환경 변수 사용: (일시적)
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./main




