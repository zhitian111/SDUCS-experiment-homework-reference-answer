#!/bin/sh

# 定义 ANSI 颜色代码
ESC="\033"
RED="${ESC}[91m"
GREEN="${ESC}[92m"
YELLOW="${ESC}[93m"
BLUE="${ESC}[94m"
RESET="${ESC}[0m"

# 检查 Python 和 Node.js
if ! command -v python >/dev/null 2>&1; then
    echo "[${YELLOW}WARNING${RESET}] Python 未找到，启动可能失败。"
fi
if ! command -v node >/dev/null 2>&1; then
    echo "[${YELLOW}WARNING${RESET}] Node.js 未找到，npx/npm 启动可能失败。"
fi

port=8000

echo "[${YELLOW}NOTICE${RESET}] 启动成功后请访问 http://127.0.0.1:${port}/ 查看结果，您可自行修改脚本设置监听端口"
sleep 1
echo "[${BLUE}INFO${RESET}] 尝试使用python启动服务"
sleep 1
python -m http.server ${port} --bind 127.0.0.1 || {
    echo "[${RED}ERROR${RESET}] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好python解释器"
    sleep 1
    echo "[${BLUE}INFO${RESET}] 尝试使用npx启动服务"
    sleep 1
    npx http-server -p ${port} -a 127.0.0.1 || {
        echo "[${RED}ERROR${RESET}] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好npx工具"
        sleep 1
        echo "[${BLUE}INFO${RESET}] 尝试使用npm启动服务"
        sleep 1
        npm run serve || {
            echo "[${RED}ERROR${RESET}] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好node.js环境和module"
            sleep 1
            echo "[${RED}ERROR${RESET}] 所有启动方式均失败，请检查网络连接或环境配置，或者尝试以管理员权限运行脚本，或自行启动服务，或使用其他方式查看页面"
            sleep 1
        }
    }
}

exit 0