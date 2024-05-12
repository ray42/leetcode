import sys
import os


currentDir = ""


# dirname is something like 0279_PerfectSquares
def setupLeetCode(dirname):
    # If dirname is empty, just return
    if not dirname:
        print('Usage: .\\setup.py 0279_PerfectSquares')
        return
    
    # Check for incorrect directory name.
    # The directory name has to contain at least
    # '1234_x'
    if len(dirname) < 6:
        print(dirname, ' is less than length 6')
        return
    
    if dirname[4] != '_':
        print(dirname, ' must start with e.g. 1234_')
        return

    os.chdir(currentDir)

    if os.path.exists(dirname):
        print(dirname, ' exists')
    else:
        os.mkdir(dirname)

    os.chdir(dirname)

    filename = dirname[0:4] + '.cpp'
    if not os.path.exists(filename):
        open(filename, 'a').close()
    else:
        print(filename, ' exists')
    
    return

def setupMultipleLeetCode(listFileName):
    with open(listFileName) as file:
        while line := file.readline():
            setupLeetCode(line.strip())

def main():
    name = sys.argv[1]
    global currentDir 
    currentDir = os. getcwd()

    if(name == "list.txt"):
        setupMultipleLeetCode(name)
    else:
        setupLeetCode(name)
        
if __name__ == "__main__":
    main()




