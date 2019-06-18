# watcher

> 一个简单的小程序，用于监测一个局域网中所有接入设备的在线时间 

> 首先配置watch.conf文件，格式为[name mac]
```
John bc:a8:a6:f3:7d:70
Mike 20:a6:c:2c:f2:b0
```

> 然后检查依赖
```
arp-scan
pandas(py3)
matplotlib(py3)
```

> 最后
```
$ ./run.sh
$ sudo ./wcr
```
