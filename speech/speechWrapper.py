#!/bin/python2

from subprocess import call

SPEECH_COMMAND = "./readFile.sh"
SPEECH_FILE = "dictation.txt"

def writeToFile(data, fileName):
	output = open(fileName, "w")
	output.write(data)
	output.close()

def dictate():
	call([SPEECH_COMMAND, SPEECH_FILE])

def speak(english):
	writeToFile(english, SPEECH_FILE)
	dictate()