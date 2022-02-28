def solution(s):
    answer = 0
    answer_str=''
    dic={'zero':0,'one':1,'two':2,'three':3,'four':4,'five':5,'six':6,'seven':7,'eight':8,'nine':9}
    temp=''
    for key,value in dic.items():
        s=s.replace(key,str(value))
    answer=int(s)
    return answer
