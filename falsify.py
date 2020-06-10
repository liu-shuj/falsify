import os
from random import uniform,choice

itersPerIn=150
maxDep=6
lenSig=6
maxT=100
maxB=600
nt=30
nb=30
nTrials=3
nSamplesO=100
nSamplesF=10
minSoFar=[float('inf'),'']

def InitRegions(curSig):
    d={}
    stepT=maxT/nt
    stepB=maxB/nb
    for i in range(1,nt+1):
        throttle=i*stepT
        for j in range(1,nb+1):
            brake=j*stepB
            sig=curSig[:]
            sig.append((throttle,brake))
            path=Model(sig)
            if path not in d:
                d[path]=[]
            d[path].append((throttle,brake))
    return d
    
def OrderRegions(regions,curSig,curDep):
    l=[]
    for regionPath in regions:
        curMin=float('inf')
        #curSum=0
        #curNum=0
        for i in range(0,nSamplesO):
            throttle,brake=SampleFromRegion(curSig,regionPath,regions)
            if((throttle,brake)==(False,False)):
                continue
            sig=curSig[:]
            sig.append((throttle,brake))
            for j in range(0,lenSig-curDep-1):
                throttle=uniform(0,maxT)
                brake=uniform(0,maxB)
                sig.append((throttle,brake))
            rb=float(Model(sig,calcRb=True))
            if(rb<minSoFar[0]):
                minSoFar[0]=rb
                minSoFar[1]=sig
                print(minSoFar)
            if(rb<0):
                print(sig)
                exit(0)
            else:
                if(rb<curMin):
                    curMin=rb
                #curSum+=rb
                #curNum+=1
        #avg=curSum/curNum if curNum!=0 else float('inf')
        l.append((regionPath,curMin))
    l.sort(key=lambda t:t[1])
    l=list(map(lambda t:t[0],l))
    return l
    
def SampleFromRegion(curSig,regionPath,regions):
    stepT=maxT/nt
    stepB=maxB/nb
    throttle,brake=choice(regions[regionPath])
    for i in range(0,nTrials):
        newT=uniform(throttle-stepT,throttle+stepT)
        newB=uniform(brake-stepB,brake+stepB)
        sig=curSig[:]
        sig.append((newT,newB))
        path=Model(sig)
        if(path==regionPath):
            return newT,newB 
    return False,False 
    
def Model(sig,calcRb=False):
    cmd='./model'
    if(calcRb==True):
        cmd+=' 1 '
    else:
        cmd+=' 0 '
    cmd+=str(itersPerIn)
    for t in sig:
        cmd+=' '
        cmd+=str(t[0])
        cmd+=' '
        cmd+=str(t[1])
    #print(cmd)
    s=os.popen(cmd).read()
    return s
    
def Falsify(curSig,curDep):
    if(curDep==maxDep):
        rb=float(Model(curSig,calcRb=True))
        if(rb<minSoFar[0]):
            minSoFar[0]=rb
            minSoFar[1]=curSig
            print(minSoFar)
        #print(rb)
        if(rb<0):
            print(curSig)
            exit(0)
        else:
            return
    regions=InitRegions(curSig)
    orderedRegions=OrderRegions(regions,curSig,curDep)
    for regionPath in orderedRegions:
        for i in range(0,nSamplesF):
            throttle,brake=SampleFromRegion(curSig,regionPath,regions)
            if((throttle,brake)==(False,False)):
                continue
            sig=curSig[:]
            sig.append((throttle,brake))
            print("Recursion")
            Falsify(sig,curDep+1)
            
Falsify([],0)
