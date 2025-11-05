from random import random as Rand
file="RESULTS"
def DEZERO(x):return(x if x!=0 else 1)
def Addition(file):
    R=["","","","",""]
    File=open(file,"a")
    Name=input("What is your name: ")
    while"0"in Name or"1"in Name or Name=="":Name=input("INVALID. Try again: ")
    File.write(Name)
    for i in range(5):
        No1=int(Rand()*8+1)
        No2=int(Rand()*8+1)
        Guess=input("What is "+str(No1)+"+"+str(No2)+"? ")
        while len(Guess)>2 or len(Guess)==0 or 0 in (j in "0123456789" for j in Guess):Guess=input("Invalid. What is "+str(No1)+"+"+str(No2)+"?")
        R[i]="1"if str(No1+No2)==Guess else"0"
        File.write(R[i])
    File.close()
    print("You got "+str(sum(int(i)for i in R)*20)+"%.")
def AllData(file):
    File=open(file,"r")
    FTXT=File.read()
    File.close()
    i,CuName,NameAr,ScoreAr=0,"",[],[]
    while i<len(FTXT):
        if"0"!=FTXT[i]and"1"!=FTXT[i]:
            CuName+=FTXT[i]
            i+=1
        else:
            if not CuName in NameAr:NameAr.append(CuName),ScoreAr.append([0,0])
            for j in range(5):
                if FTXT[i]=="1":ScoreAr[NameAr.index(CuName)][0]+=1
                else:ScoreAr[NameAr.index(CuName)][1]+=1
                i+=1
            CuName=""
    for i in range(len(NameAr)):print(NameAr[i]+" got "+str(ScoreAr[i][0])+" correct and "+str(ScoreAr[i][1])+" wrong, which is "+str((ScoreAr[i][0]/(ScoreAr[i][0]+ScoreAr[i][1]))*100)+"% of questions correct.")
def SomeData(file):
    File=open(file,"r")
    FTXT=File.read()
    File.close()
    i,CuName,ReqName,ScoreAr=0,"",input("Who would you like to search for? "),[0,0]
    while i<len(FTXT):
        if"0"!=FTXT[i]and"1"!=FTXT[i]:
            CuName+=FTXT[i]
            i+=1
        else:
            if CuName==ReqName:
                for j in range(5):
                    if FTXT[i]=="1":ScoreAr[0]+=1
                    else:ScoreAr[1]+=1
                    i+=1
            else:i+=5
            CuName=""
    print(ReqName+" got "+str(ScoreAr[0])+" correct and "+str(ScoreAr[1])+" wrong, which is "+str((ScoreAr[0]/DEZERO(ScoreAr[0]+ScoreAr[1]))*100)+"% of questions correct."if ReqName in FTXT else ReqName+" does not exist.")
def ChangeFile():
    global file
    file=input("Enter new file: ")
def Menu(INP="Enter command",Func=[],Arg=[]):
    Command=input(INP+": ")
    for i in range(len(Func)):
        if i>=len(Arg):
            if Command==str(i):Func[i]()
        else:
            if Command==str(i):Func[i](Arg[i])
while 1:Menu(Func=[Addition,AllData,SomeData,quit,ChangeFile],Arg=[file,file,file],INP="Enter: 0 to take the test, 1 to view all scores, 2 to view specific scores, 3 to quit, or 4 to change the source file")
