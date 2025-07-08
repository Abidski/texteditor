#Inspired from https://github.com/cococry/lyssa

CPP = g++
LIBS =  -lGL -lglfw -lGLEW

SOURCE_DIR = src
BIN_DIR = bin

all : 
	${CPP} ${SOURCE_DIR}/*.cpp -o ${BIN_DIR}/editor ${LIBS}

build:
	mkdir ${BIN_DIR}

run: 
	cd bin && ./editor

