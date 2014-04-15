#!/bin/python2
import time
import json
import httplib2
import gflags

from apiclient.discovery import build
from oauth2client.file   import Storage
from oauth2client.client import OAuth2WebServerFlow
from oauth2client.tools  import run

def getTodaysTimeRange():
	day = time.localtime().tm_mday
	nform = '%Y-%m-' + str(day) + 'T00:00:00%z'
	time_min = time.strftime(nform)
	#
	nform = '%Y-%m-' + str(day + 1) + 'T00:00:00%z'
	time_max = time.strftime(nform)
	#
	return [time_min, time_max]

def getClientSecrets():
	secret_file = open("secret/client_secret.json", "r")
	secrets = json.loads(secret_file.read())
	secret_file.close()
	#
	return {"id": secrets['installed']['client_id'], "secret": secrets['installed']['client_secret']}

def getAPIkey():
	public_data = open("secret/other.json", "r")
	apiInfo = json.loads(public_data.read())
	public_data.close()
	#
	return apiInfo['public_api']['API_key']

def getRegisteredUsers():
	user_index = open("accounts.json", "r")
	userInfo = json.loads(user_index.read())
	user_index.close()
	#
	return userInfo

def getAccountAuthFlow():
	secrets = getClientSecrets()
	#
	FLAGS = gflags.FLAGS
	return OAuth2WebServerFlow(
	    client_id=secrets['id'],
	    client_secret=secrets['secret'],
	    scope='https://www.googleapis.com/auth/calendar',
	    user_agent='tyrone/0.0')

def createCalendarService(user_id):
	#
	storage = Storage('secret/accounts/' + user_id + '.dat')
	credentials = storage.get()
	http = httplib2.Http()
	#
	if credentials is None or credentials.invalid == True:
		credentials = run(getAccountAuthFlow(), storage)
		#print "FATAL: No data found for " + user_id
		#exit(1)
	else:
		credentials.refresh(http)
	#
	http = credentials.authorize(http)
	#
	return build(serviceName='calendar', version='v3', http=http,
		developerKey=getAPIkey())

def getCalendars(calendarService):
	page_token = None
	calendars = []
	#
	while True:
		calendar_list = calendarService.calendarList().list(pageToken=page_token).execute()
		#
		for calendar_list_entry in calendar_list['items']:
			calendars += [calendar_list_entry['id']]
		#
		page_token = calendar_list.get('nextPageToken')
		#
		print '.',
		if not page_token:
			break
	#
	return calendars

def getTodaysEvents(calendars, calendarService):
	time_range = getTodaysTimeRange()
	events = []
	#
	for calID in calendars:
		#
		page_token = None
		#
		while True:
			todaysEvents = calendarService.events().list(
				calendarId=calID, 
				timeMin=time_range[0], timeMax=time_range[1],
				pageToken=page_token).execute()
			#
			events += todaysEvents['items']
			page_token = todaysEvents.get('nextPageToken')
			#
			print '.',
			if not page_token:
				break
	#
	return events

def timestampToEnglish(timestamp):
	# RFC-3339 Timestamps can be:
	# 2011-08-30T13:22:53.108Z
	# or
	# 2011-08-30T09:30:16.768-04:00
	# but later is sent from google
	clockTime = timestamp.split('T')[1].split('-')[0].split(':')
	#
	hour   = int(clockTime[0])
	minute = clockTime[1]
	#
	if (hour > 11):
		if (hour > 12):
			hour -= 12
		return str(hour) + ":" + minute + " p.m."
	else:
		return str(hour) + ":" + minute + " a.m."

def toEnglish(personName, events):
	if not events:
		return "Nothing planned for you today, " + personName
	#
	breifing = "Your schedule for today, " + personName + ". "
	#
	for event in events:
		# Print event summary
		breifing += event['summary'] + " "
		# Check for day long events
		if 'dateTime' in event['start']:	
			breifing += "at " + timestampToEnglish(event['start']['dateTime']) + " . "
		else:
			breifing += "is today. "
	#
	return breifing

def main():
	users = getRegisteredUsers()
	schedules = ""
	#
	for user_id in users.keys():
		#
		calendarService = createCalendarService(user_id)
		#
		calendars = getCalendars(calendarService)
		#
		events = getTodaysEvents(calendars, calendarService)
		#
		schedules += toEnglish(users[user_id]['Name'], events) + "\n"
	#
	return schedules

#if __name__ == "__main__":
#	writeToFile(main(), SPEECH_FILE)
#	dictate()