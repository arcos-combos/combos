array = []
maxi = 0
mini = 99999
lis = [0]*60
mean = 0
total = 0

def function(src, dst):
    global array, maxi, mini, lis, mean, total
    acum=0
    # open source file
    with open(src) as f:
        array = [[float(x) for x in line.split()] for line in f]
    # open destination file
    with open(dst, 'w+') as f2:
        for i in array:
            for j in range(0, int(i[0])):
            	f2.write(str(i[1])+'\n')
            maxi = max(maxi,i[1])
            mini = min(mini,i[1])    
            mean+=(i[0]*i[1])
            total+=i[0]

    mean/=total

'''
    for i in array:
        lis[int(i[1]/2.5)]+=int(i[0])
        
    with open('gnuplot_results', 'w+') as f:
        f.write("Flops\tFrecuency\n")
        index = 1
        for i in lis:
            f.write(str(index) + "\t" + str(i) + "\n")
            index+=1

    with open('gnuplot_results_pdf', 'w+') as f:
        f.write("Flops\tProbability_density_function\n")
        index = 1
        for i in lis:
            aux = i*1.0/total
            aux = str.format("{0:.3f}", aux)
            f.write(str(index) + "\t" + aux + "\n")
            index+=1
            
    with open('gnuplot_results_cdf', 'w+') as f:
        f.write("Flops\tCumulative_distribution_function\n")
        index = 1
        for i in lis:
            aux = i*1.0/total
            acum += aux
            f.write(str(index) + "\t" + str(acum) + "\n")
            index+=1

    
            
        for i in array:
            for j in range(0, int(i[0]/5)):
                f.write(str(i[1]).replace('.', ',') + '\n')
            '''
