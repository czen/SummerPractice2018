import re
import sys

if __name__ == "__main__":
    fileIn = open("g100_100.dot")
    fileOut = open("matrix.txt","w")
    
    edgeExpr = re.compile("(^[0-9]+) -> ([0-9]+)")
    
    edges = []
    maxNumber = 0
    for line in fileIn:
        m = edgeExpr.match(line)
        
        if (m != None):
            edgeStart = int(m.group(1))
            edgeEnd = int(m.group(2))
            edges.append([edgeStart,edgeEnd])
            maxNumber = max(maxNumber, edgeStart,edgeEnd)
        
    print(maxNumber)
    print(edges)
    
    for i in range(0,maxNumber):
        for j in range(0,maxNumber):
            if ([i,j] in edges):
                fileOut.write("1,")
                #sys.stdout.write("1 ")
                #print("1 ")
            else:
                fileOut.write("0,")
                #sys.stdout.write("0")
                #print("0 ")
        #print(" ")
        fileOut.write("\n")