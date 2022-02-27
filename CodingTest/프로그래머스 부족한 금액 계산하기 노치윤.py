def solution(price, money, count):
    answer = -1
    req=count*(count+1)*price/2
    answer=-money+req
    if answer<0:
        answer=0
    return answer
