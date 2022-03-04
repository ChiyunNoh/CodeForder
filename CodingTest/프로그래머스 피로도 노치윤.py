import itertools

def solution(k, dungeons):
    answer = -1
    nPr=list(itertools.permutations(dungeons))
    for i in range(len(nPr)):
        tired=k
        cnt=0
        for j in range(len(nPr[i])):
            if tired>=nPr[i][j][0]:
                tired-=nPr[i][j][1]
                cnt+=1
        if answer<cnt:
            answer=cnt
    return answer
