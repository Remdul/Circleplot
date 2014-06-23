#Opens file and seperates each data entry in to it's own section
f = open("sample_data.txt")
plotPoint = []
for line in f:
    data = line.split(",")
    #Checks to see if it is in meters and if it isn't converts it to meters
    if (data[2][-2:] == 'KM'):
        string = data[2]
        
        #Checks for a decimal place and gets rid of it then adds the correct amount of zeroes
        if string.find(".") != -1:
            string = string[:string.find(".")] + string[string.find(".")+1:]
            data[2] = string[:-2] + "00M" 
        else:
            data[2] = string[:-2] + "000M"
            
    plotPoint.append(data)

#Goes through every possible combination and prints it out to make sure
#everything got entered correctly
for entry in plotPoint:
    print(entry[0])
    print(entry[1])
    print(entry[2])
    print(entry[3])
 
 #Calling for data would be plotPoint[0][0]
 #X is the entry and Y is name, location, radius, description respectfully [0,1,2,3]

#Pauses command line
input()
