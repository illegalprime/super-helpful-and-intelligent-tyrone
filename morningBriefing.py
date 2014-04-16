#!/bin/python2
import os
import sys

from subprocess import call
from time import sleep

sys.path.append("proprietary/ForecastIO")
sys.path.append("proprietary/GoogleCalendar")
sys.path.append("speech/")

import getTodaysWeather
import getTodaysEvents
import speechWrapper

os.chdir("proprietary/ForecastIO")

print "Getting weather info:",
weather = getTodaysWeather.main()
os.chdir("../..")

os.chdir("proprietary/GoogleCalendar")

print "\nGetting today's calendar:",

users = getTodaysEvents.getRegisteredUsers().values()
people = ""
i = 0

while ( i < len(users) - 1):
	people += users[i]['Name'] + ", "
	i += 1

if i != 0:
	people += " and "

people += users[i]['Name']

schedule = getTodaysEvents.main()
os.chdir("../..")

os.chdir("speech/")

english = "Good morning, " + people + ". " + weather + schedule
print

speechWrapper.speak(english)

sleep(1)

speechWrapper.speak("Starting Pandora Radio.")

os.chdir("../proprietary/Pandora")

call(["./startPandora.sh"])