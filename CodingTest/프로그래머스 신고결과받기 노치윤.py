def solution(id_list, report, k):
    answer = [0 for i in range(len(id_list))]
    report_tmp=[]
    cnt=[0 for i in range(len(id_list))]
    idx_dict={}
    for i in range(len(id_list)):
        idx_dict[id_list[i]]=i
        tmp=[0 for i in range(len(id_list))]
        report_tmp.append(tmp)
    
    for i in range(len(report)):
        a,b=report[i].split()
        if report_tmp[idx_dict[a]][idx_dict[b]]==0:
            report_tmp[idx_dict[a]][idx_dict[b]]+=1
    
    for i in range(len(id_list)):
        sum=0
        for j in range(len(id_list)):
            sum+=report_tmp[j][i]
        if sum>=k:
            cnt[i]=1
    
    for i in range(len(id_list)):
        for j in range(len(id_list)):
            if cnt[j]==1 & report_tmp[i][j]==1:
                answer[i]+=1
    return answer
