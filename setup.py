import sys
import os




def setupLeetCode(dirname):
    if os.path.exists(dirname):
        print(dirname, ' exists')
    else:
        os.mkdir(dirname)

    os.chdir(dirname);

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
    if(name == "list.txt"):
        setupMultipleLeetCode(name)
    else:
        setupLeetCode(name)
        
if __name__ == "__main__":
    main()




