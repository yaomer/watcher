#!/bin/bash

TMPFILE=$(mktemp /tmp/tmp.XXXXX)
RESFILE="./mac.txt"

# 扫描10次
SCAN_TIMES=10
while [ $SCAN_TIMES -gt 0 ]
do
    arp-scan -l | grep "^[0-9][0-9][0-9][.]" >> "$TMPFILE"
    ((SCAN_TIMES--))
done

if [ -f "$RESFILE" ]; then
    : > "$RESFILE"
fi

# 提取MAC地址
cut -f 2 "$TMPFILE" >> "$RESFILE"
: > "$TMPFILE"

# 过滤掉重复的MAC地址
sort "$RESFILE" | uniq >> "$TMPFILE"
: > "$RESFILE"
cat "$TMPFILE" >> "$RESFILE"
rm "$TMPFILE"
