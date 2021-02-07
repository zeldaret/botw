#!/usr/bin/bash

# Example usage:
# Search for a function and update uking_functions.csv to include its mangled name
#   ./workflow.sh mangle orderparam::doassign
# Diff a function (in this example, OrderParam::doAssign, -v is equivalent to --source in diff.py)
#   ./workflow.sh diff -v _ZN4ksys3evt10OrderParam13addParamActorEPNS_3act8BaseProcERN4sead14SafeStringBaseIcEE
# Search for mangle name and diff (-f turns off interaction)
#   ./workflow.sh mad -v -f orderparam::doassign
# Get ready to pr
#   ./workflow.sh check

#I use this to copy files from and to WSL. Valid options: ON, OFF, AUTO
#ON:   Enabled. Will give warning if WORKING_FILES or FILE_SYNC_PY does not exist
#OFF:  Disabled. file sync is completely ignored in workflow
#AUTO: Enable file sync if WORKING_FILES and FILE_SYNC_PY exist
FILE_SYNC=AUTO
FILE_SYNC_PY=../file-sync.py

#A list of source code being worked on. If exists, clang-format will only format these files which is faster
WORKING_FILES=../file-list.txt
#Path to uking_functions.csv
UKING_FUNCTIONS=data/uking_functions.csv    
#Path to temporarily put the output of tools/print_decomp_symbols.py
SYMBOL_OUT=build/symbols.txt                
#Path to diff.py
DIFF_PY=./diff.py
#Path to print_decomp_symbols.py
PRINT_DECOMP_SYMBOLS_PY=tools/print_decomp_symbols.py
#Path to check.py
CHECK_PY=tools/check.py
#clang-format
CLANG_FORMAT=clang-format

STDOUT_COLOR='\033[1;36m'
STDIN_COLOR='\033[1;33m'
STDERR_COLOR='\033[1;31m'
WORKFLOW_TAG='[Workflow]'

OPTION_PATTERN=-[a-zA-Z]
# Flag to turn off interaction in mangle and mad
# In mangle, the functions will only be printed. uking_functions.csv will not update
# In mad, automatically proceed to diff without confirming mangled name
FLAG_MANGLE_NO_INTERACTION='-f'
# Equivalent to --source in diff.py
FLAG_DIFF_SOURCE='-v'
# Only used in file sync
FLAG_WRITE_BACK='-w'

#Helpers
print_info(){
    echo -e "$STDOUT_COLOR$WORKFLOW_TAG \033[0m$@"
}
print_error(){
    echo -e "$STDOUT_COLOR$WORKFLOW_TAG$STDERR_COLOR Error: \033[0m$@"
}
print_prompt(){
    echo -e "$STDIN_COLOR$WORKFLOW_TAG $@\033[0m"
}

if [[ ${FILE_SYNC} == "ON" ]]
then
    if ! test -f $WORKING_FILES || ! test -f $FILE_SYNC_PY
    then
        print_error "File sync is on, but working file list or sync script is not found. File sync will be skipped."
        FILE_SYNC=OFF
    fi
elif [[ ${FILE_SYNC} == "AUTO" ]]
then
    if ! test -f $WORKING_FILES || ! test -f $FILE_SYNC_PY
    then
        FILE_SYNC=OFF
    else
        FILE_SYNC=ON
    fi 
fi

args=$@
func=$1
arg=

for possible_arg in ${@:2}
do
    if ! [[ $possible_arg =~ ${OPTION_PATTERN} ]]
    then
        arg=$possible_arg
        break
    fi
done

has_option(){
    option=$1
    [[ " ${args[@]} " =~ " ${option} " ]]
}
do_sync(){
    if [[ ${FILE_SYNC} == "ON" ]]
    then
        print_info "Syncing"
        $FILE_SYNC_PY -l $WORKING_FILES $1
    fi
}
do_build(){
    print_info "Building"
    ninja -C build
}
do_diff(){
    print_info "Diffing $1"
    if has_option $FLAG_DIFF_SOURCE
    then
        $DIFF_PY --source $1
    else
        $DIFF_PY $1
    fi
}
do_format(){
    print_info "Formatting source code"
    if test -f $WORKING_FILES
    then
        cat $WORKING_FILES | xargs $CLANG_FORMAT -i --verbose
    else
        find src -name *.h | xargs $CLANG_FORMAT -i
        find src -name *.cpp | xargs $CLANG_FORMAT -i
    fi
}
check_status(){
    if [[ $1 -ne 0 ]]; then print_error "Workflow error. Check output above."; exit $1; fi
}

case $func in
sync|s )
    do_sync;;
build|b )
    do_sync && do_build;;
mangle|m )
    while [[ -z ${arg} ]]
    do
        print_error "Function name is empty!"
        read -p "$(print_prompt "Enter function string to search: ")" arg
    done
    do_sync && do_build 
    rc=$? && check_status $rc
    print_info "Finding $arg"
    $PRINT_DECOMP_SYMBOLS_PY -a > $SYMBOL_OUT
    grep -i $arg $SYMBOL_OUT --color=always

    if ! has_option ${FLAG_MANGLE_NO_INTERACTION}
    then
        mangled_name=$(grep -i $arg $SYMBOL_OUT | grep -o '_.*$' | head -n 1 | sed 's/).*$//g')
        print_prompt "Enter mangled function name:"
        mangled_name_in=
        read -p "($mangled_name) " mangled_name_in 
        if [[ -n $mangled_name_in ]]
        then
            mangled_name=$mangled_name_in
        fi

        grep -ni $arg $UKING_FUNCTIONS --color=always
        line=$(grep -ni $arg $UKING_FUNCTIONS | grep -o '^[0-9]*' | head -n 1)
        read -p "$(print_prompt "Enter function line number ($line): ")" line_in 
        if [[ -n $line_in ]]
        then
            line=$line_in
        fi
        while [[ -z ${line} ]]
        do
            print_error "Line number cannot be empty"
            read -p "$(print_prompt "Enter function line number: ")" line 
        done

        print_info "Ready to edit $UKING_FUNCTIONS"
        echo "Changing"
        current=$(sed $line"q;d" $UKING_FUNCTIONS)
        echo "    $current"
        echo "To"
        after=$(echo $current | perl -pe 's/,(.(?!,))*$/,'$mangled_name'/g')
        echo "    $after"
        read -p "$(print_prompt "Press enter to continue, n to exit ")" yn
        case $yn in
            [Nn]* ) exit;;
            *) ;;
        esac
        sed -i $line"s/.*/$after/g" $UKING_FUNCTIONS && print_info "OK"
    fi;;
diff|d )
    while [[ -z ${arg} ]]
    do
        print_error "Mangled name is empty!"
        read -p "$(print_prompt "Enter mangled name to diff: ")" arg
    done
    do_diff $arg;;
mad )
    while [[ -z ${arg} ]]
    do
        print_error "Function name is empty!"
        read -p "$(print_prompt "Enter function string to mangle and diff: ")" arg
    done
    do_sync && do_build 
    rc=$? && check_status $rc
    print_info "Finding $arg"
    $PRINT_DECOMP_SYMBOLS_PY -a > $SYMBOL_OUT
    grep -i $arg $SYMBOL_OUT --color=always
    mangled_name=$(grep -i $arg $SYMBOL_OUT | grep -o '_.*$' | head -n 1 | sed 's/).*$//g')
    if ! has_option ${FLAG_MANGLE_NO_INTERACTION} 
    then
        print_prompt "Enter mangled function name:"
        mangled_name_in=
        read -p "($mangled_name) " mangled_name_in 
        if [[ -n $mangled_name_in ]]
        then
            mangled_name=$mangled_name_in
        fi
    fi
    do_diff $mangled_name;;
check|c )
    do_sync && do_format
    if has_option $FLAG_WRITE_BACK
    then
        do_sync -r
    fi
    do_build && print_info "Checking match..." && $CHECK_PY;
    rc=$? && check_status $rc
    print_info "OK";;
*)
    print_error "Unknown command $func"
    if [[ ${FILE_SYNC} == "ON" ]]
    then
    echo "s|sync                 Sync the directory"
    fi
    echo "b|build                Build"
    echo "m|mangle <search>      Search for the mangled name of a function and update uking_functions.csv"
    echo "         [-f]            Search only, do not update function list"
    echo "d|diff   <function>    Diff function"
    echo "         [-v]            verbose, show source when diffing"
    echo "c|check                Format source code and run tools/check.py"
    if [[ ${FILE_SYNC} == "ON" ]]
    then
    echo "         [-w]            sync formatted code"
    fi
    echo " |mad    <search>      Mangle and diff. Search for the mangled name of a function and diff it"
    echo "         [-v]            verbose, show source when diffing"
    echo "         [-f]            force, do not confirm function name before diffing";;


esac
