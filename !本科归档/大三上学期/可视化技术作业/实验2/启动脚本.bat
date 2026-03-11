@echo off

set "ESC="
set "RED=%ESC%[91m"
set "GREEN=%ESC%[92m"
set "YELLOW=%ESC%[93m"
set "BLUE=%ESC%[94m"
set "RESET=%ESC%[0m"

where python >nul 2>&1
if errorlevel 1 echo [WARNING] Python 未找到，启动可能失败。
where node >nul 2>&1
if errorlevel 1 echo [WARNING] Node.js 未找到，npx/npm 启动可能失败。

set port=8000

echo [%YELLOW%NOTICE%RESET%] 启动成功后请访问 http://127.0.0.1:%port%/ 查看结果，您可自行修改脚本设置监听端口
timeout /t 1 >nul
echo [%BLUE%INFO%RESET%] 尝试使用python启动服务
timeout /t 1 >nul
python -m http.server %port% --bind 127.0.0.1
if errorlevel 1 (
    echo [%RED%ERROR%RESET%] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好python解释器
    timeout /t 1 >nul
    echo [%BLUE%INFO%RESET%] 尝试使用npx启动服务
    timeout /t 1 >nul
    npx http-server -p %port% --a 127.0.0.1
    if errorlevel 1 (
        echo [%RED%ERROR%RESET%] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好npx工具
        timeout /t 1 >nul
        echo [%BLUE%INFO%RESET%] 尝试使用npm启动服务
        timeout /t 1 >nul
        npm run serve
        if errorlevel 1 (
            echo [%RED%ERROR%RESET%] 启动失败，请检查网络连接或端口是否被占用，或是否已配置好node.js环境和module
            timeout /t 1 >nul
            echo [%RED%ERROR%RESET%] 所有启动方式均失败，请检查网络连接或环境配置，或者尝试以管理员权限运行脚本，或自行启动服务，或使用其他方式查看页面
            timeout /t 1 >nul
            )
    )
)

exit /b 0