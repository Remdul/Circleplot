import re
import sys
class Point:
    #Constructor
    def __init__(self, line=None):
        self.centerpoint = ''
        self.radius_meters = 0
        self.name = ''
        self.description = ''
        if line is not None:
            #remove leading and trailing whitespace
            line = line.strip()
            fields = line.split(',')
            self.name = fields[0].strip()
            self.centerpoint = fields[1].strip()
            #use regular expression to seperate into 
            #number and multiplyer
            match = re.search(r"([\d\.]+)\s*(K?M)", fields[2] )
            print '->%s< ->%s<-' % ( match.group(1), match.group(2))
            self.radius_meters = float(match.group(1))
            if match.group(2) == 'KM':
                self.radius_meters *= 1000
                self.radius_meters = int(self.radius_meters)
            self.description = fields[3].strip('" ')

    #Automatically convert to string if needed
    def __str__(self):
        #make use of python's printf style string formattting
        result = "Name: %s\n" % self.name
        result += "Description: %s\n" % self.description
        result += "Centerpoint: %s\n" % self.centerpoint
        result += "Radius: %d m" % self.radius_meters
        return result

def main():
    filename = "sample_data.txt"
    plotPoint = []
    if len(sys.argv) == 2:
        #Let command line override default file if specified
        filename = sys.argv[1]
    f = open(filename, "r")
    for line in f:
        #Pass each line to the constructor and add the result to the array 
        plotPoint.append(Point(line))
        #Pauses command line
    
    for point in plotPoint:
        print str(point)
    dummy = raw_input()

#by doing this our python script can both be imported as a module
#and ran as a program.
if __name__ == '__main__':
    main()
