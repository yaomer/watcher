#!/bin/bash

# ping.sh 不显示输出
# ping.sh any-arg 显示一些结果

PLATFORM=$(uname -s)
PING="ping -t 1"
BEGIN=2
END=254
SHOWRES=0

if [ $# -gt 0 ]; then
    SHOWRES=1
fi

# 清空ARP缓存，需root权限
if [ "$PLATFORM" == "Darwin" ]; then
    arp -ad > /dev/null
elif [ "$PLATFORM" == "Linux" ]; then
    ip neigh flush dev en0
else
    echo "Unknown Platform"
    exit 1
fi

function add_space()
{
    if [ $BEGIN -lt 10 ]; then
        echo "    "
    elif [ $BEGIN -lt 100 ]; then
        echo "   "
    else
        echo "  "
    fi
}

# try to ping all ips
# [ ping *[2 : 254] and arp -a ] time about 6 mins
while [ $BEGIN -le $END ]; do
    IP="192.168.3.$BEGIN"
    if [ $SHOWRES -eq 1 ]; then
        echo -n "$IP$(add_space)"
        $PING $IP | tail -n 1
    else
        $PING $IP > /dev/null
    fi
    ((BEGIN++))
done
if [ $SHOWRES -eq 1 ]; then
    echo ""
fi

TMPFILE=$(mktemp /tmp/tmp.XXXXX)
RESFILE="./mac.txt"

if [ -f "$RESFILE" ]; then
    : > "$RESFILE"
else
    touch "$RESFILE"
fi

arp -a >> "$TMPFILE"

# 提取MAC地址
i=1
while read -r line
do
    MAC=$(awk 'NR=='$i' {print $4}' "$TMPFILE")
    echo "$MAC" >> "$RESFILE"
    ((i++))
done < "$TMPFILE"
rm "$TMPFILE"

# 删除无效的MAC地址
if [ "$PLATFORM" == "Darwin" ]; then
    sed -i "" ''/incomplete/'d' "$RESFILE"
elif [ "$PLATFORM" == "Linux" ]; then
    sed -i ''/incomplete/'d' "$RESFILE"
fi

if [ $SHOWRES -eq 1 ]; then
    echo "$RESFILE: "
    cat "$RESFILE"
fi
