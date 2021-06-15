#!/bin/bash

array=(
    src/KingSystem/GameData/gdtCommonFlags.cpp
    src/KingSystem/GameData/gdtCommonFlagsUtils.cpp
    src/KingSystem/GameData/gdtSpecialFlags.cpp
)

for file in "${array[@]}"
do
    echo > $file
    git update-index --assume-unchanged $file
done
