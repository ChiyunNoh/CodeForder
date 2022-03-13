import math

def isPrime(n):
    
    n=int(n)
    if n==1:
        return False
    for i in range(2,int(math.sqrt(n))+1):
        if n%i==0:
            return False
    return True

def toK(n,k):
    num=""
    while(n!=0):
        num=str(n%k)+num
        n=n//k
    return num

def solution(n, k):
    answer = 0
    K_notation=toK(n,k)
    num=""
    for i in K_notation:
        if i=='0':
            if(num!=""):
                if(isPrime(num)):
                    answer=answer+1
            num=""
        else:
            num=num+i
    if(num!=""):
        if(isPrime(num)):
            answer=answer+1
    return answer
