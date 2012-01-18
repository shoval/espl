import os, sys, time

class Dirwatch:
    """(paths:[str], func:callable, delay:float)
    Continuously monitors the paths and their subdirectories
    for changes.  If any files or directories are modified,
    the callable 'func' is called with a list of the modified paths of both
    files and directories. 
    """
    def __init__(self, paths, func, delay=1.0):
        self.paths = paths
        self.func = func
        self.delay = delay
        self.all_files = {}
        self.remaining_files = {}
        self.changed_list = []
        
    # Basic principle: all_files is a dictionary mapping paths to
    # modification times.  We repeatedly crawl through the directory
    # tree rooted at 'path', doing a stat() on each file and comparing
    # the modification time.

    def __crawl(self, dirname, files):
        # Traversal function for directories
        for filename in files:
            path = os.path.join(dirname, filename)

            try:
                t = os.stat(path)
            except os.error:
                # If a file has been deleted between os.path.walk()
                # scanning the directory and now, we'll get an
                # os.error here.  Just ignore it -- we'll report
                # the deletion on the next pass through the main loop.
                continue

            mtime = self.remaining_files.get(path)
            if mtime is not None:
                # Record this file as having been seen
                del self.remaining_files[path]
                # File's mtime has been changed since we last looked at it.
                if t.st_mtime > mtime:
                    self.changed_list.append(path)
            else:
                # No recorded modification time, so it must be
                # a brand new file.
                self.changed_list.append(path)

            # Record current mtime of file.
            self.all_files[path] = t.st_mtime

    # Main loop
    def watch(self):
        while True:
            self.changed_list = []
            self.remaining_files = self.all_files.copy()
            self.all_files = {}
            for path in self.paths:
                os.path.walk(path, lambda a, d, f: self.__crawl(d, f) , None)
                removed_list = self.remaining_files.keys()
                if self.changed_list or removed_list:
									self.all_files = self.func(self.changed_list, removed_list, self.all_files)
            time.sleep(self.delay)

if __name__ == '__main__':
    def f (changed_files, removed_files):
        print changed_files
        print 'Removed', removed_files

    dirs = sys.argv[1:]
    if not dirs:
        dirs = ["."]

    
    Dirwatch(dirs, f, 1).watch()
