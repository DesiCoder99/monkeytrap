#!/usr/bin/python

import sys, os, re;

dTs = 0
oldTs=-1

for l in sys.stdin:
	l2=l.rstrip()
	t = l2.split(' ')
	if len(t) < 2:
		continue

	ts = t[1].split(':')
	
	tsInMs = (int(ts[0])*3600 + int(ts[1])*60 + float(ts[2]))*1000
	#print '%f -- %s ffffffffffffff\n' % ( tsInMs, t[1])
	if (oldTs > 0):
		dTs = tsInMs - oldTs

	#t[0]=tsInMs
	oline = "%f %f %s" % (dTs, tsInMs, " ".join(t))

	print oline
	oldTs = tsInMs
