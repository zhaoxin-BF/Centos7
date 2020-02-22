rsconfig = {
		_id: "rs0"
		members:[
		{_id: 0, host: "117.50.109.148:27020", priority: 3},
		{_id: 1, host: "117.50.106.133:27020", priority: 2},
		{_id: 2, host: "117.50.21.81:27020", priority: 1}
	]
}

rs.initiate(rsconfig)
sleep(10000)
printjson(rs.status())
