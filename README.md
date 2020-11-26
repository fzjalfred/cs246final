# cs246final


git clone git@github.com:fzjalfred\cs246final.git

###注意事项###

写的时候独立开出分支（branch）
不要在主分区（master）上操作
只有在确保debug完 再放到主分区上进行合并

总结创建与合并分支命令如下：

查看分支：git branch

创建分支：git branch name

切换分支：git checkout name

创建+切换分支：git checkout –b name

合并某分支到当前分支：git merge name
##Example##
git checkout master #从当前分支dev回到主分支
git merge –no-ff -m “这次改动的注释” dev   # 把dev合并到master上。 no fastforward

删除分支：git branch –d name



