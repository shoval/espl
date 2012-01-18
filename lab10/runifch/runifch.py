#!/usr/bin/python
import dirwatch, os, sys, time, subprocess

def runprog(changed_files, removed_files, all_files):
	com = sys.argv[1].split()
	com.append("")
	for path in changed_files:
		com[len(com)-1] = path
		print subprocess.check_output(com)
		try:
			t = os.stat(path)
		except os.error:
			continue
		all_files[path] = t.st_mtime
	return all_files

if __name__ == '__main__':
	def f (changed_files, removed_files):
		print changed_files
		print 'Removed', removed_files
		
	dirs = sys.argv[2:]
	if not dirs:
		dirs = ["."]
	dirwatch.Dirwatch(dirs, runprog, 1).watch()