#!/bin/bash

TMPFILE=$(mktemp /tmp/tmp.XXXXX)
RESFILE="./mac.txt"

# 扫描10次
SCAN_TIMES=9
while [ $SCAN_TIMES -ge 0 ]
do
    echo -ne "\033[31mSCANING ... $SCAN_TIMES\033[0m\r"
    echo -ne "\033[?25l"
    arp-scan -l | grep "^[0-9][0-9][0-9][.]" >> "$TMPFILE"
    ((SCAN_TIMES--))
done
echo ""

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
