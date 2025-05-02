#!/bin/bash
rm -f diary.txt

echo "Test pdadd: Add entries"
printf "But I loved you so\nPlease let me go\n.\n" | ./pdadd 2023-10-10
printf "德洛丽丝·黛————人道主义，国际主义和福利国家的无罪女王——转身面向你。她手上拖着一只旅行箱，似乎很着急。\n.\n" | ./pdadd 2023-10-11

echo -e "\nTest pdlist: List all entries"
./pdlist

echo -e "\nTest pdlist with range: 2023-10-10 to 2023-10-10"
./pdlist 2023-10-10 2023-10-10

echo -e "\nTest pdshow: Show diary 2023-10-10"
./pdshow 2023-10-10

echo -e "\nTest pdremove: Remove diary 2023-10-10"
./pdremove 2023-10-10

echo -e "\nEntries after removal:"
./pdlist