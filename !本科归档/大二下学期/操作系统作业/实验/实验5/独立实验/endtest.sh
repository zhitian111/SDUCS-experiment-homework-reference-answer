#!/bin/bash

echo -e "The following processes will be killed:\n"
ps | grep user
ps | grep barber
ps | grep barbershop
echo -e "\n"

pkill user
pkill barber
pkill barbershop

echo -e "\nAll done."

ipcrm -a
