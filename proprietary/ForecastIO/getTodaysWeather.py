#!/bin/python2

import forecastio
import json

def getAPIKey():
	api_file = open("secret/api.json", "r")
	apiInfo  = json.loads(api_file.read())
	api_file.close()
	return apiInfo['key']

def getLocations():
	locations_file = open("accounts.json", "r")
	locations      = json.loads(locations_file.read())
	locations_file.close()
	return locations

def getForecastServices():
	key  = getAPIKey()
	locs = getLocations()
	forecasts = {}
	#
	for loc in locs.keys():
		print '.',
		forecasts[loc] = forecastio.load_forecast(key, locs[loc][0], locs[loc][1])
	#
	return forecasts

def getCurrentTemp(forecastService):
	print '.',
	return forecastService.currently().temperature

def getDailyHigh(forecastService):
	print '.',
	return forecastService.daily().data[0].temperatureMax

def getTodaysWeather():
	english = ""
	services = getForecastServices()
	#
	for location in services:
		english += "It is currently " + str(getCurrentTemp(services[location])) + \
			" degrees in " + location + \
			" with a high today of " + str(getDailyHigh(services[location])) + " .\n"
	#
	return english

def main():
	return getTodaysWeather()