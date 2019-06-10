# watcher

首先配置mac.conf文件，格式为[name mac]
```
John bc:a8:a6:f3:7d:70
Mike 20:a6:c:2c:f2:b0
```

然后修改ping.sh中的`IP="xxx.$BEGIN"`

配置完成后，
```
$ ./run.sh
$ sudo ./wcr
```
