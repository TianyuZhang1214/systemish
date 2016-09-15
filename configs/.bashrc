alias ls='ls --color'
alias src='source ~/.bash_profile'
alias gitd='git difftool'
alias gtid='git difftool'
alias gitshort='git rev-parse --short HEAD'
alias sc='screen -dRR'

# Avoid duplicates in bash history
export HISTCONTROL=ignoreboth:erasedups

# CUDA
export PATH=$PATH:/usr/local/cuda/bin/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

PATH=$PATH:/users/akalia/systemish/scripts
export PATH

function a() {
	ssh akaliaNode-$1.RDMA.fawn.apt.emulab.net
}

alias psmain='ps -afx | grep main'

# Remove SHM regions
function drop_shm()                                                                 
{                                                                                   
    echo "Dropping SHM entries"                                                     
                                                                                    
    for i in $(ipcs -m | awk '{ print $1; }'); do                                   
        if [[ $i =~ 0x.* ]]; then                                                   
            sudo ipcrm -M $i 2>/dev/null                                            
        fi                                                                          
    done                                                                            
}  
