import plotly
import plotly.graph_objs as go

nameArr={
	0: [1000,3000,5000,10000],
	2: range(1,11),
	3: range(1,11),
	4: range(1,11),
	5: range(1,11),

}

numElemsArr={
	0: 4,
	2: 10,
	3: 10,
	4: 10,
	5: 10
}

for i in range(0,6):
	if i == 1:
		continue
	filename = "out/out_"+`i`+".txt"
	with open(filename,"r") as f:
		currLabel = None
		labels=[]
		objs = {}
		num_elems=0
		for line in f:
			if "files" in line:
				currLabel = line.strip()
				if currLabel not in labels:
					labels.append(currLabel)
			else:
				lineArr = line.split(',')
				num_elems = len(lineArr)-1
				if lineArr[0] not in objs:
					objs[lineArr[0]] = []
				appendLineArr=[currLabel]+lineArr[1:]
				objs[lineArr[0]].append(appendLineArr)
		graph_x = labels
		for graph_num in objs.keys():
			data = objs[graph_num]
			dataArr = {}
			#print num_elems
			for j in range(0,numElemsArr[i]):
				currDataArr = []
				for x in data:
					if j not in dataArr:
						dataArr[j] = []
					dataArr[j].append(x[j+1].strip())
			
			traceArr=[]
			#print dataArr
			for elem in dataArr.keys():
				# print "elem"+`elem`
				# print "i"+`i`
				# print nameArr[i][elem]
				traceArr.append(go.Bar(
				 	x=graph_x,
					y=dataArr[elem],
			 		name=`nameArr[i][elem]`
			 	))
			layout = go.Layout(barmode='group')
			fig = go.Figure(data=traceArr, layout=layout)
			plot_url = plotly.offline.plot(fig, filename=`i`+"_"+`graph_num`)

