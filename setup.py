import sys
import os


currentDir = ""


def setupLeetCode(dirname):
    # If dirname is empty, just return
    if not dirname:
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




