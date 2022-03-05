def intersection_point(line1, line2):
    a,b,e = line1
    c,d,f = line2
    if a*d == b*c:
        return None
    x = (b*f-e*d)/(a*d-b*c)
    y = (e*c-a*f)/(a*d-b*c)
    if x == int(x) and y == int(y):
        return (int(x),int(y))

def solution(line):
    answer = []
    points = set()
    
    for i in range(len(line)-1):
        line1=line[i]
        for j in range(i+1,len(line)):
            line2=line[j]
            point =intersection_point(line1, line2)
            if point:
                points.add(point)
    
    point_x=[x[0] for x in points]
    max_x=max(point_x)
    min_x=min(point_x)
    
    point_y=[y[1] for y in points]
    max_y=max(point_y)
    min_y=min(point_y)
    
    answer=['.'*(max_x-min_x+1)]*(max_y-min_y+1)
    for point in points:
        x,y=point
        answer[-y+max_y]=answer[-y+max_y][0:x-min_x]+'*'+answer[-y+max_y][x-min_x+1:]

    return answer
