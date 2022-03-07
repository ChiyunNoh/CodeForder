dic={'A':1,'E':2,'I':3,'O':4,'U':5}

def iter(num,cnt):
    if num==10000:
        return cnt
    temp=num
    for i in range(5):
        if i==4:
            return cnt+(temp-1)*781
        if (temp%10!=0) & (temp%10!=1):
            temp=temp-1
            for j in range(i):
                temp=temp*10
                temp=temp+5
            break
        elif temp%10==1 :
            temp=temp-1
            for j in range(i):
                temp=temp*10
            break
        else:
            temp=temp//10
    return iter(temp,cnt+1)
    
def solution(word):
    answer = 0
    num=0
    for i in word:
        num=num*10
        num=num+dic[i]
    num=num*(10**(5-len(word)))
    answer=iter(num,1)
    return answer
