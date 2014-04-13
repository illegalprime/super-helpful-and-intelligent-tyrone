#!/bin/python2
#  Creates calendar.dat an OAuth thing to let program access
#  a user's google calendar without knowing their password

# Time stamps are 'RFC 3339 timestamp'

from apiclient.discovery import build
from oauth2client.file   import Storage
from oauth2client.client import OAuth2WebServerFlow
from oauth2client.tools  import run

import httplib2
import gflags
import time

import json

calendars = {"Michael": []}
events    = {"Michael": []}
#daylight_savings = True    # Not actually used
#time_zone = 'US/Central'
#fmt = '%Y-%m-%dT%H:%M:%S%z'

day = time.localtime().tm_mday
nform = '%Y-%m-' + str(day) + 'T00:00:00%z'
time_min = time.strftime(nform)
nform = '%Y-%m-' + str(day + 1) + 'T00:00:00%z'
time_max = time.strftime(nform)
print "From " + time_min + " to " + time_max

f = open("secret/client_secret.json", "r")
secrets = json.loads(f.read())
f.close()

FLAGS = gflags.FLAGS
FLOW = OAuth2WebServerFlow(
    client_id=secrets['installed']['client_id'],
    client_secret=secrets['installed']['client_secret'],
    scope='https://www.googleapis.com/auth/calendar',
    user_agent='tyrone/0.0')

storage = Storage('secret/calendar.dat')
credentials = storage.get()
http = httplib2.Http()

if credentials is None or credentials.invalid == True:
	credentials = run(FLOW, storage)
else:
	credentials.refresh()

http = credentials.authorize(http)

f = open("secret/other.json")
secrets = json.loads(f.read())
f.close()

service = build(serviceName='calendar', version='v3', http=http,
	developerKey=secrets['public_api']['API_key'])

page_token = None

while True:
	calendar_list = service.calendarList().list(pageToken=page_token).execute()
	for calendar_list_entry in calendar_list['items']:
		calendars['Michael'] += [calendar_list_entry['id']]
	page_token = calendar_list.get('nextPageToken')
	print '.'
	if not page_token:
		break


for name in calendars:
	for calID in calendars[name]:
		page_token = None
		while True:
			todaysEvents = service.events().list(calendarId=calID, timeMax=time_max, timeMin=time_min, pageToken=page_token).execute()
			print '.'
			events[name] += todaysEvents['items']
			page_token = todaysEvents.get('nextPageToken')
			if not page_token:
				break


for name in events:
	print name + ":"
	for event in events[name]:
		# Print event summary
		print "\t" + event['summary'],
		# Check for day long events
		if 'dateTime' in event['start']:	
			print "at " + event['start']['dateTime'].split('T')[1].split('-')[0]
		else:
			print "today"







"""
zone = pytz.timezone(time_zone)

date_start = datetime.datetime.now()
date_start = date_start.replace(hour=0, minute=0, second=0, microsecond=0)

one_day = datetime.timedelta(days=1)

date_end = date_start + one_day

time_min = zone.localize(date_start).strftime(fmt)
time_max = zone.localize(date_end).strftime(fmt)
"""