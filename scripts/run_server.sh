#!/bin/sh

if [ -f $LED_MON_EXEC ];
then
    $LED_MON_EXEC
else
    echo "$LED_MON_EXEC not found"
    exit
fi