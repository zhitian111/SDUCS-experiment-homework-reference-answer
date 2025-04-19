#!/bin/bash
echo -e "these process will be killed\n"
ps | grep control
ps | grep writer
ps | grep reader
pkill control
pkill writer
pkill reader
echo -e "all process killed\n"
