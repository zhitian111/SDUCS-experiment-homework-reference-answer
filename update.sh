#!/bin/bash
echo -e "\n\033[1;33m开始git仓库更新...\033[0m\n"
echo -e "\n\033[1;36m当前分支：\033[0m\n"
git -P branch
if ! git status | grep -q "nothing to commit, working tree clean"; then
  git add --all
  echo -e "\n\033[1;36m当前状态：\033[0m\n"
  git status
  echo -e "\n\033[1;33m请输入提交信息:\033[0m\n"
  read -r commit_msg
  echo -e "\n\033[1;36m提交状态为：\033[0m\n"
  git commit -m "$commit_msg"
  echo -e "\n\033[1;35m是否要推送到远程仓库？(y/other)\033[0m"
  read -r push_choice
  if [ "$push_choice" = "y" ] || [ "$push_choice" = "Y" ] ; then 
    echo -e "\n\033[1;33m正在推送至远程仓库...\033[0m\n"
    git push github main
  fi  
else
  echo -e "\n\033[1;36m当前状态：\033[0m\n"
  git status
  echo -e "\n\033[1;33m当前没有需要提交的更改\033[0m\n"
fi
echo -e "\n\033[1;32mgit仓库更新结束\033[0m\n"
