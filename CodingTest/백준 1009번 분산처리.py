import sys 
input = sys.stdin.readline

li=[[0],[1],[2,4,8,6],[3,9,7,1],[4,6],[5],[6],[7,9,3,1],[8,4,2,6],[9,1]]
t = int(input())
for i in range(t):
    line=input().split()
    a=int(line[0])
    b=int(line[1])
    leng=len(li[a%10])
    print(li[a%10][b%leng-1])
