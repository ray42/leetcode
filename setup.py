import sys
import os

# This program prints Hello, world!
dirname = sys.argv[1]

if os.path.exists(dirname):
    print(dirname, ' exists')
else:
    os.mkdir(dirname)
    print(dirname, ' created')

os.chdir(dirname);

filename = dirname[0:4] + '.cpp'
if not os.path.exists(filename):
    open(filename, 'a').close()
    print(filename, ' created')
else:
    print(filename, ' exists')


