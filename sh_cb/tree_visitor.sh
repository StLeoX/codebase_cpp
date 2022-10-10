#! /bin/sh
# sheel脚本实现tree的递归遍历功能

# macros
branch_vline="│   "     #Branch vertical line 
branch_null="    "      #null separation branch 
middle_branch_end="├── "  #middle file branch
last_branch_end="└── "    #the last file branch
branch_sum="" 
filecount=0
directorycount=0

# callbacks
# modify origin to `github.com/$user/$repo.git`
function git_seturl_cb() {

}

# display git info, include `filepath`, `remote url`
function git_info_cb(){

}

function tree(){
    # pre-traversal:
    # Is this a git repo?
    is_git = 0
    for file in *;
    do
      if [ test $file -ef ".git" ]; then
        $is_git==1
        break
      fi
    done
    if [ ! $is_git ]; then
        return
    fi

    # do-traversal
    local num=0
    for file in *;  
    do  
        thelastfile=`ls |wc -l`
        num=$((num+1))
        if [[ $thelastfile -eq $num ]]; then
                if [ -f "$file" ]; then
                    filecount=$((filecount+1))
                    if [ -x "$file" ];then
                        echo -e "${branch_sum}$last_branch_end\033[1;32m$file\033[0m"
                    else
                        echo -e "${branch_sum}$last_branch_end$file"
                    fi
                fi    
                if [ -d "$file" ]; then
                    directorycount=$((directorycount+1))   
                    echo -e "${branch_sum}$last_branch_end\033[1;34m$file\033[0m"
                    branch_sum=${branch_sum}${branch_null}
                    cd "$file"
                    tree  
                    cd ..  
                    branch_sum=${branch_sum%${branch_null}}
                fi              
        else                
            if [ -f "$file" ]; then
                    filecount=$((filecount+1))
                    if [ -x "$file" ];then
                        echo -e "${branch_sum}$middle_branch_end\033[1;32m$file\033[0m"
                    else
                        echo "${branch_sum}${middle_branch_end}$file"
                    fi                       
            fi    
            if [ -d "$file" ]; then 
                    directorycount=$((directorycount+1))   
                    echo -e "${branch_sum}${middle_branch_end}\033[1;34m$file\033[0m" 
                    branch_sum=${branch_sum}${branch_vline}
                    cd "$file"  
                    tree  
                    cd ..  
                    branch_sum=${branch_sum%${branch_vline}}  
            fi              
        fi     
    done  
}

function main(){
if [ -z "$1" ]; then
    echo -e "\033[1;34m.\033[0m"
else
    echo -e "\033[1;34m$1\033[0m"
    cd $1
fi
if [[ $? -eq 0 ]]; then
    tree
    echo
    echo "count: $directorycount directories,  $filecount files"
fi
}

main() $@