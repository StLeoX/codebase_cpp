## 实用shell脚本

### github_archive_installer.sh

作用：从GitHub Release页下载文件，尤其是针对Rust编写的多平台小工具。  
支持的仓库类型：Rust， 使用：
> curl -fsSL https://path/to/github_archive_installer.sh | bash

### tree_visitor.sh

sheel脚本实现tree的递归遍历功能，支持多种回调函数 回调函数：

- git status
- git remote set-url
- cargo status

